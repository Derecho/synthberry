#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include "imidisource.h"
#include "inoteobserver.h"
#include "wave.h"
#include <vector>
#include <cstdint>

/*! \brief Top-level class representing a synthesizer setup
 *
 * The Synthesizer class represents a complete synthesizer system that consists
 * of an input, output and modules such as an oscillator and envelope generator.
 *
 */
template <class SampleType> class Synthesizer
{
public:
    Synthesizer();
    ~Synthesizer();
    void setMidiSource(PMidiSource &source);
    void addNoteObserver(PNoteObserver &observer);
    // TODO addSynthModule(PSynthModule &module);
    // TODO setAudioOutput(PAudioOutput &output);

private:
    PMidiSource midiSource;
    std::vector<PNoteObserver> noteObservers;
    // TODO std::vector<PSynthModule> synthModules;
    // TODO PAudioOutput audioOutput;
    std::vector<Wave<SampleType> > waves;
};

#endif  // SYNTHESIZER_H
