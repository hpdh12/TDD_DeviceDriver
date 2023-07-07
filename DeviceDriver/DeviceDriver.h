#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

    enum
    {
        COUNT_SHOULD_READ = 5,
    };

protected:
    FlashMemoryDevice* m_hardware;
};