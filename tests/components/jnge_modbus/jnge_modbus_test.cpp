#include <gtest/gtest.h>
#include "common.h"

namespace esphome::jnge_modbus::testing {

// crc16 (CRC-16/MODBUS)

TEST(Crc16Test, ZeroLengthIsAllOnes) {
  // CRC of empty data starts at 0xFFFF but no XOR is done -> 0xFFFF
  EXPECT_EQ(crc16(nullptr, 0), 0xFFFF);
}

TEST(Crc16Test, SingleByte) {
  // crc16({0x01}) should match CRC-16/MODBUS standard
  uint8_t data[] = {0x01};
  uint16_t crc = crc16(data, 1);
  // Verify self-consistency: crc of (data + crc_lo + crc_hi) == 0
  uint8_t extended[] = {0x01, static_cast<uint8_t>(crc & 0xFF), static_cast<uint8_t>(crc >> 8)};
  EXPECT_EQ(crc16(extended, 3), 0x0000);
}

TEST(Crc16Test, FrameCrcSelfCheck) {
  // A correctly framed message has CRC-16 of 0x0000 when the CRC bytes are appended.
  std::vector<uint8_t> data = {0xAB, 0xCD, 0xEF};
  uint16_t crc = crc16(data.data(), static_cast<uint8_t>(data.size()));
  data.push_back(static_cast<uint8_t>(crc & 0xFF));
  data.push_back(static_cast<uint8_t>(crc >> 8));
  EXPECT_EQ(crc16(data.data(), static_cast<uint8_t>(data.size())), 0x0000);
}

// Frame parsing and device dispatch

TEST(JngeModbusParseTest, ValidFrameDispatchedToDevice) {
  TestableJngeModbus modbus;
  MockJngeModbusDevice device;
  device.set_address(0x01);
  modbus.register_device(&device);

  auto frame = make_response_frame(0x01, 0x03, {0xAB, 0xCD});
  modbus.feed(frame);

  EXPECT_EQ(device.call_count, 1);
  EXPECT_EQ(device.last_function, 0x03);
  ASSERT_EQ(device.received_data.size(), 2u);
  EXPECT_EQ(device.received_data[0], 0xAB);
  EXPECT_EQ(device.received_data[1], 0xCD);
}

TEST(JngeModbusParseTest, Function04Dispatched) {
  TestableJngeModbus modbus;
  MockJngeModbusDevice device;
  device.set_address(0x02);
  modbus.register_device(&device);

  auto frame = make_response_frame(0x02, 0x04, {0x00, 0x78, 0x00, 0x00});
  modbus.feed(frame);

  EXPECT_EQ(device.call_count, 1);
  EXPECT_EQ(device.last_function, 0x04);
  EXPECT_EQ(device.received_data.size(), 4u);
}

TEST(JngeModbusParseTest, TwoFramesDispatchedTwice) {
  TestableJngeModbus modbus;
  MockJngeModbusDevice device;
  device.set_address(0x01);
  modbus.register_device(&device);

  auto frame = make_response_frame(0x01, 0x03, {0x11, 0x22});
  modbus.feed(frame);
  modbus.feed(frame);

  EXPECT_EQ(device.call_count, 2);
}

TEST(JngeModbusParseTest, ErrorFunctionRejected) {
  TestableJngeModbus modbus;
  MockJngeModbusDevice device;
  device.set_address(0x01);
  modbus.register_device(&device);

  // Bit 7 set in function byte -> error frame, rejected at byte 1
  bool result = modbus.parse_jnge_modbus_byte_(0x01);  // address
  EXPECT_TRUE(result);
  result = modbus.parse_jnge_modbus_byte_(0x83);  // function with error bit
  EXPECT_FALSE(result);
  EXPECT_EQ(device.call_count, 0);
}

TEST(JngeModbusParseTest, BadCrcRejected) {
  TestableJngeModbus modbus;
  MockJngeModbusDevice device;
  device.set_address(0x01);
  modbus.register_device(&device);

  auto frame = make_response_frame(0x01, 0x03, {0xAB, 0xCD});
  frame.back() ^= 0xFF;  // corrupt CRC high byte
  modbus.feed(frame);

  EXPECT_EQ(device.call_count, 0);
}

TEST(JngeModbusParseTest, UnknownAddressNotDispatched) {
  TestableJngeModbus modbus;
  MockJngeModbusDevice device;
  device.set_address(0x99);
  modbus.register_device(&device);

  auto frame = make_response_frame(0x01, 0x03, {0xAB, 0xCD});
  modbus.feed(frame);

  EXPECT_EQ(device.call_count, 0);
}

TEST(JngeModbusParseTest, NoRegisteredDeviceDoesNotCrash) {
  TestableJngeModbus modbus;
  auto frame = make_response_frame(0x01, 0x03, {0xAB, 0xCD});
  modbus.feed(frame);
}

TEST(JngeModbusParseTest, PartialFrameDoesNotDispatch) {
  TestableJngeModbus modbus;
  MockJngeModbusDevice device;
  device.set_address(0x01);
  modbus.register_device(&device);

  auto frame = make_response_frame(0x01, 0x03, {0xAB, 0xCD, 0xEF, 0x12});
  for (size_t i = 0; i < frame.size() - 2; i++)
    modbus.parse_jnge_modbus_byte_(frame[i]);

  EXPECT_EQ(device.call_count, 0);
}

}  // namespace esphome::jnge_modbus::testing
