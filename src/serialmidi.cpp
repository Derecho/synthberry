#include <iostream>
#include "serialmidi.h"

SerialMidi::SerialMidi(std::string serialPath) :
    IMidiSource(),
    serialStream(serialPath),
{
    serialStream.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_38400);
    serialStream.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
    serialStream.SetNumOfStopBits(1);
    serialStream.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
    serialStream.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);
}

SerialMidi::~SerialMidi()
{
    serialStream.Close();
}

void SerialMidi::run()
{
    unsigned int pos = 0;
    unsigned int bytesLeft = 0;
    unsigned char buf[16];

    while(serialStream.good()) {
        unsigned char c = serialStream.get();

        // TODO Remove
        if(c < 0xf0)  // Don't output System Real Time Messages
            std::cout << "Received byte: " << std::hex << (unsigned int)c << std::endl;

        if(bytesLeft == 0) {
            if(pos > 0) {
                // No more bytes left, position was not zero, we've finished receiving a message
                std::cout << "Received message:";
                for(int i = 0; i < pos; i++) {
                    std::cout << " " << std::hex << (unsigned int)buf[i];
                }
                std::cout << std::endl;
                pos = 0;
            }

            if((c >= 0x80) & (c < 0x90)) {
                // Note Off
                buf[0] = c;
                bytesLeft = 2;
                pos++;
            }
            else if((c >= 0x90) & (c < 0xa0)) {
                // Note On
                buf[0] = c;
                bytesLeft = 2;
                pos++;
            }
        }
        else {
            buf[pos] = c;
            bytesLeft--;
            pos++;
        }
    }
}
