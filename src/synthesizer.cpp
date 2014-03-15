#include "synthesizer.h"

/*!
 * Construct a Synthesizer.
 *
 * When working with 16-bit samples, set uint16_t as the SampleType.
 *
 * \tparam SampleType Integer type for storing sample in
 */
template <class SampleType> Synthesizer<SampleType>::Synthesizer()
{
}

template <class SampleType> Synthesizer<SampleType>::~Synthesizer()
{
}

/*! \brief Set a midi source
 *
 * Set an object implementing IMidiSource as the midi source for this Synthesizer.
 *
 * \param source Shared pointer to IMidiSource implementation
 *
 */
template <class SampleType> void Synthesizer<SampleType>::setMidiSource(
        PMidiSource &source)
{
    midiSource = source;
}

/*! \brief Add a note observer
 *
 * Add an object implementing INoteObserver to Synthesizer. The object will be
 * notified of note changes from midi sources in Synthesizer.
 *
 * \param observer Shared pointer to INoteObserver implementation
 *
 */
template <class SampleType> void Synthesizer<SampleType>::addNoteObserver(
        PNoteObserver &observer)
{
    noteObservers.push_back(observer);
}

// Instantiate template class
template class Synthesizer<uint16_t>;
