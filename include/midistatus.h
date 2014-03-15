#ifndef MIDISTATUS_H
#define MIDISTATUS_H

#include <cstdint>

enum MidiStatus : uint8_t
{
    None = 0,
    NoteOff = 0x80,
    NoteOn = 0x90,
    KeyPressure = 0xA0,
    ControlChange = 0xB0,
    ProgramChange = 0xC0,
    ChannelPressure = 0xD0,
    PitchBend = 0xE0
};

#endif  // MIDISTATUS_H
