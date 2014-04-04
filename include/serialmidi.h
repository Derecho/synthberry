#ifndef SERIALMIDI_H
#define SERIALMIDI_H

#include <string>
#include <SerialStream.h>
#include "imidisource.h"
#include "notes.h"
#include "midistatus.h"

/*! \brief Class for using a serial connection as a MIDI source.
 *
 * SerialMidi is a class implementing IMidiSource, parsing MIDI messages
 * received on the given serial port.
 *
 * The baudrate is statically set to 38400, which corresponds to 31250 on a
 * Raspberry Pi with modified serial clock.
 *
 * SerialMidi parses NoteOn and NoteOff messages destined to channel 0.
 *
 */
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
