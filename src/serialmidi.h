#ifndef SERIALMIDI_H
#define SERIALMIDI_H

#include <string>
#include <SerialStream.h>
#include "imidisource.h"
#include "notes.h"

class SerialMidi : public IMidiSource
{
public:
    SerialMidi(std::string serialPath);
    ~SerialMidi();
    void run();
    Notes getNotes();

private:
    LibSerial::SerialStream serialStream;
    Notes notes;
};

#endif  // SERIALMIDI_H
