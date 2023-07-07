#include <stdexcept>
#include "DeviceDriver.h"

using namespace std;

class ReadFailException : public exception
{
public:
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int value = (int)(m_hardware->read(address));
    for (int i = 0; i < 4; i++)
    {
        if (value != (int)(m_hardware->read(address))) {
			throw ReadFailException();
        }
    }
    return value;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}