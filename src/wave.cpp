#include <cstdlib>
#include <cmath>
#include "wave.h"

template <class SampleType> Wave<SampleType>::Wave(uint16_t bitrate) :
    buffer(nullptr),
    bufferSize(0),
    bitrate(bitrate),
    changed(true),
    lowestFreq(0)
{
}

template <class SampleType> Wave<SampleType>::~Wave()
{
    if(buffer)
        free(buffer);
}

/*! \brief Set a new formula
 *
 * Clear any current formulas and set a new one to be used for generating the
 * wave buffer. Used by oscillators.
 *
 * \param func Initial formula
 *
 */
template <class SampleType> void Wave<SampleType>::setNewFormula(FormulaFunction func)
{
    formula.clear();
    changed = true;
    lowestFreq = 0;
    addToFormula(func);
}

/*! \brief Add an extra formula
 *
 * Add an additional formula to Wave. Used by SynthModule subclasses.
 *
 * \param func Effect formula
 *
 */
template <class SampleType> void Wave<SampleType>::addToFormula(FormulaFunction func)
{
    changed = true;
    formula.push_back(func);
}

/*! \brief Set a new lowest frequency
 *
 * As Wave bases its buffer size on the length of a full period of the wave, it
 * needs to know the lowest frequency component present in it. When setting or
 * adding formulas, call this method to update the buffer size.
 *
 * Should you call this method with a higher freq than was used earlier, nothing
 * happens.
 *
 * \param freq New lowest frequency in Hz
 *
 */
template <class SampleType> void Wave<SampleType>::setLowestFrequency(float freq)
{
    if((freq < lowestFreq) || (lowestFreq == 0)) {
        changed = true;
        lowestFreq = freq;
        bufferSize = std::ceil(bitrate/freq) * sizeof(SampleType);
        if(buffer)
            free(buffer);
        buffer = static_cast<SampleType *>(malloc(bufferSize));
        if(buffer == nullptr)
            throw std::bad_alloc();
    }
}

/*! \brief Retrieve the lowest frequency
 *
 * Retrieve the lowest known frequency component (in Hz) that was set on an
 * earlier occasion.
 *
 */
template <class SampleType> float Wave<SampleType>::getLowestFrequency()
{
    return lowestFreq;
}

/*! \brief Update the wave buffer
 *
 * After setting a formula, adding a formula, or setting a new lowest frequency,
 * you need to update the buffer with newly generated values before a sound can
 * be played.
 *
 * You should avoid unnecessary calls to this method, calling it once after you
 * are ready with the Wave is best.
 *
 */
template <class SampleType> void Wave<SampleType>::updateBuffer()
{
    if(changed) {
        changed = false;
        for(auto func : formula)
            func(buffer, bufferSize, bitrate);
    }
}
