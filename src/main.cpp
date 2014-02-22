#include <iostream>
#include "serialmidi.h"
#include "log.h"

int main(int argc, char *argv[])
{
    LOG("Synthberry starting...");

    IMidiSource *midi = new SerialMidi("/dev/ttyAMA0");
    midi->run();

    return 0;
}
