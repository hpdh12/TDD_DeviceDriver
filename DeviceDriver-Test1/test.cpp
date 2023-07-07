#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriverTest, CheckDriverRead5Times) {
	FlashMemoryDeviceMock mockDevice;
	DeviceDriver driver(&mockDevice);

	EXPECT_CALL(mockDevice, read)
		.Times(5)
		.WillRepeatedly(Return(0));

	driver.read(0x4);
}