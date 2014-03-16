#ifndef BASICWAVE_H
#define BASICWAVE_H

#include "wave.h"

/*! \brief Representation of a basic wave
 *
 * BasicWave is the simplest implementation of the abstract Wave class.
 * Oscillators create instances of BasicWave, which can later on be upgraded to
 * EnvelopedWave objects should the need occur.
 *
 */
template <class SampleType> class BasicWave : public Wave<SampleType>
{
public:
    BasicWave(uint16_t bitrate);
    ~BasicWave();
    SampleType getNextSample();
    // TODO EnvelopedWave<SampleType> toEnvelopedWave();

private:
    std::size_t position;
};

#endif  // BASICWAVE_H
