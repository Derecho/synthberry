#include <iostream>
#include "serialmidi.h"
#include "debugobserver.h"
#include "synthesizer.h"
#include "log.h"

int main(int argc, char *argv[])
{
    LOG("Synthberry starting...");

    PMidiSource midi(new SerialMidi("/dev/ttyAMA0"));
#ifdef DEBUG
    PNoteObserver debugObserver(new DebugObserver);
    midi->getNotes().registerObserver(debugObserver);
    LOG("DebugObserver registered");
#endif
    midi->run();

    // Code below isn't used yet
    Synthesizer<uint16_t> synth;
    synth.setMidiSource(midi);
#ifdef DEBUG
    synth.addNoteObserver(debugObserver);
#endif

    return 0;
}
