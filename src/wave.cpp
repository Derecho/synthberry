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

template <class SampleType> void Wave<SampleType>::setNewFormula(FormulaFunction func)
{
    formula.clear();
    changed = true;
    lowestFreq = 0;
    addToFormula(func);
}

template <class SampleType> void Wave<SampleType>::addToFormula(FormulaFunction func)
{
    changed = true;
    formula.push_back(func);
}

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

template <class SampleType> float Wave<SampleType>::getLowestFrequency()
{
    return lowestFreq;
}

template <class SampleType> void Wave<SampleType>::updateBuffer()
{
    if(changed) {
        changed = false;
        for(auto func : formula)
            func(buffer, bufferSize, bitrate);
    }
}
