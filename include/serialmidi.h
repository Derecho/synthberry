#ifndef SERIALMIDI_H
#define SERIALMIDI_H

#include <string>
#include <SerialStream.h>
#include "imidisource.h"
#include "notes.h"
#include "midistatus.h"

class SerialMidi : public IMidiSource
{
public:
    SerialMidi(std::string serialPath);
    ~SerialMidi();
    void run();
    Notes& getNotes();

private:
    void parseMessage();
    LibSerial::SerialStream serialStream;
    uint8_t channel;
    Notes notes;
    MidiStatus status;
    uint8_t data[2];  // MIDI Channel Messages have 2 data bytes at most
};

#endif  // SERIALMIDI_H
