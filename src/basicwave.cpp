#include "basicwave.h"

template <class SampleType> BasicWave<SampleType>::BasicWave(uint16_t bitrate) :
    Wave<SampleType>(bitrate),
    position(0)
{
}

template <class SampleType> BasicWave<SampleType>::~BasicWave()
{
}

template <class SampleType> SampleType BasicWave<SampleType>::getNextSample()
{
    if(position == this->bufferSize)
        position = 0;

    return this->buffer[position++];
}
