#include <iostream>
#include <SerialStream.h>

int main(int argc, char *argv[])
{
    LibSerial::SerialStream serialStream("/dev/ttyAMA0");
    serialStream.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_38400);
    serialStream.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
    serialStream.SetNumOfStopBits(1);
    serialStream.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
    serialStream.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);

    while(serialStream.good())
    {
        char c = serialStream.get();
        std::cout << "Received byte: " << std::hex << (int)c << std::endl;
    }

    serialStream.Close();
}

