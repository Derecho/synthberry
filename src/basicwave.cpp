#include "basicwave.h"

/*!
 * Construct a BasicWave
 *
 * When working with 16-bit samples, set uint16_t as the SampleType.
 *
 * \tparam SampleType Integer type for storing sample in
 */
template <class SampleType> BasicWave<SampleType>::BasicWave(uint16_t bitrate) :
    Wave<SampleType>(bitrate),
    position(0)
{
}

template <class SampleType> BasicWave<SampleType>::~BasicWave()
{
}

/*! \brief Retrieve next sample to play
 *
 * Retrieve the next sample from the buffer to play. If the end of the buffer
 * has been reached, getNextSample() will automatically return to the beginning
 * of the buffer.
 *
 */
template <class SampleType> SampleType BasicWave<SampleType>::getNextSample()
{
    if(position == this->bufferSize)
        position = 0;

    return this->buffer[position++];
}
