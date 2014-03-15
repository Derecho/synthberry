#include "synthesizer.h"

template <class SampleType> Synthesizer<SampleType>::Synthesizer()
{
}

template <class SampleType> Synthesizer<SampleType>::~Synthesizer()
{
}

template <class SampleType> void Synthesizer<SampleType>::setMidiSource(
        PMidiSource &source)
{
    midiSource = source;
}
template <class SampleType> void Synthesizer<SampleType>::addNoteObserver(
        PNoteObserver &observer)
{
    noteObservers.push_back(observer);
}

// Instantiate template class
template class Synthesizer<uint16_t>;
