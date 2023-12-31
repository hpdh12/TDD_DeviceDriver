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

class DeviceDriverFixture : public Test
{
public:
	DeviceDriverFixture()
	{
		driver = new DeviceDriver(&mockDevice);
	}

	FlashMemoryDeviceMock mockDevice;
	DeviceDriver *driver;

};

TEST_F(DeviceDriverFixture, CheckDriverRead5Times) {
	EXPECT_CALL(mockDevice, read)
		.Times(DeviceDriver::COUNT_SHOULD_READ)
		.WillRepeatedly(Return(0));

	driver->read(0x4);
}

TEST_F(DeviceDriverFixture, ReadExceptionWhenValueIsDiff) {
	EXPECT_CALL(mockDevice, read)
		.WillOnce(Return(1))
		.WillRepeatedly(Return(0));

	EXPECT_THROW(driver->read(0x4), ReadFailException);
}

TEST_F(DeviceDriverFixture, WritetoCleanArea)
{
	EXPECT_CALL(mockDevice, write)
		.Times(1);

	EXPECT_CALL(mockDevice, read)
		.Times(1)
		.WillOnce(Return(DeviceDriver::VALUE_OF_CLEAN_AREA));
	
	driver->write(0x1000000, 0x12);
}

TEST_F(DeviceDriverFixture, WritetoNotCleanArea)
{
	EXPECT_CALL(mockDevice, read)
		.Times(1)
		.WillOnce(Return(0x12));

	EXPECT_THROW(driver->write(0x1000000, 0x12), WriteFailException);
}