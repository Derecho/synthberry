#ifndef SERIALMIDI_H
#define SERIALMIDI_H

#include <string>
#include <SerialStream.h>
#include "imidisource.h"

class SerialMidi : public IMidiSource
{
    public:
        SerialMidi(std::string serialPath);
        ~SerialMidi();
        void run();

    private:
        LibSerial::SerialStream serialStream;
}

#endif  // SERIALMIDI_H
