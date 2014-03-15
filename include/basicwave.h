#ifndef BASICWAVE_H
#define BASICWAVE_H

#include "wave.h"

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
