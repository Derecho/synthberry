#ifndef BASICWAVE_H
#define BASICWAVE_H

#include "wave.h"

template <class SampleType> class BasicWave : public Wave<SampleType>
{
public:
    BasicWave(uint16_t bitrate);
    ~BasicWave();
    // TODO EnvelopedWave<SampleType> toEnvelopedWave();

private:
};

#endif  // BASICWAVE_H
