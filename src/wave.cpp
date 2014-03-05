#include <cstdlib>
#include <cmath>
#include "wave.h"

Wave::Wave(uint16_t bitrate) :
    bitrate(bitrate),
    changed(true),
    lowestFreq(0)
{
}

void Wave::setNewFormula(std::function<void()> func)
{
    formula.clear();
    changed = true;
    lowestFreq = 0;
    addToFormula(func);
}

void Wave::addToFormula(std::function<void()> func)
{
    changed = true;
    formula.push_back(func);
}

void Wave::setLowestFrequency(float freq)
{
    if((freq < lowestFreq) || (lowestFreq == 0)) {
        changed = true;
        lowestFreq = freq;
        bufferSize = std::ceil(bitrate/freq) * sizeof(uint16_t);
        free(buffer);
        buffer = static_cast<uint16_t *>(malloc(bufferSize));
        if(buffer == nullptr)
            throw std::bad_alloc();
    }
}

float Wave::getLowestFrequency()
{
    return lowestFreq;
}

void Wave::updateBuffer()
{
    if(changed) {
        changed = false;
        // TODO Fill buffer with all result of all formulas
    }
}
