#include "basicwave.h"

template <class SampleType> BasicWave<SampleType>::BasicWave(uint16_t bitrate) :
    Wave<SampleType>(bitrate)
{
}

template <class SampleType> BasicWave<SampleType>::~BasicWave()
{
}
