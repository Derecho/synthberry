#include <iostream>
#include "serialmidi.h"

SerialMidi::SerialMidi(std::string serialPath) :
    serialStream(serialPath),
    channel(0),  // Hardcoded for now
    status(MidiStatus::None)
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
    uint8_t pos = 0;
    uint8_t bytesLeft = 0;

    while(serialStream.good()) {
        uint8_t c = serialStream.get();

        if(bytesLeft == 0) {
            // Not expecting data at this moment

            if(pos > 0) {
                // We have just finished receiving a message
                pos = 0;
                parseMessage();
            }

            if(c < 0x80) {
                // Data received, reuse last status
                data[pos++] = c;
                if(!(status == MidiStatus::ProgramChange) &&
                    !(status == MidiStatus::ChannelPressure))
                    bytesLeft = 1;
            }
            else if((c > 0x7F) && (c < 0xF0)) {
                // Status byte of channel message
                if((c & 0x0F) == channel) {
                    // Message destined to our channel
                    status = MidiStatus((c & 0xF0));
                    if((status == MidiStatus::ProgramChange) ||
                        (status == MidiStatus::ChannelPressure))
                        bytesLeft = 1;
                    else
                        bytesLeft = 2;
                }
            }
        }
        else {
            // Data bytes
            data[pos++] = c;
            bytesLeft--;
        }
    }
}

Notes& SerialMidi::getNotes()
{
    return notes;
}

void SerialMidi::parseMessage()
{
    switch(status) {
        case MidiStatus::NoteOff:
            notes.removeNote(data[0]);
            break;
        case MidiStatus::NoteOn:
            if(data[1] == 0)
                notes.removeNote(data[0]);  // Disguised NoteOff
            else
                notes.addNote(data[0], data[1]);
            break;
        default:
            break;
    }
}
