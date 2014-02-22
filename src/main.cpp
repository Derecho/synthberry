#include <iostream>
#include "serialmidi.h"

int main(int argc, char *argv[])
{
    std::cout << "Synthberry starting..." << std::endl;

    IMidiSource *midi = new SerialMidi("/dev/ttyAMA0");
    midi->run();

    return 0;
}
