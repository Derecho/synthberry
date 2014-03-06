#ifndef WAVE_H
#define WAVE_H

#include <functional>
#include <vector>
#include <cstdint>

template <class SampleType> class Wave
{
public:
    Wave(uint16_t bitrate);
    virtual ~Wave(){};
    virtual SampleType getNextSample() = 0;
    void setNewFormula(std::function<void()> func);
    void addToFormula(std::function<void()> func);
    void setLowestFrequency(float freq);
    float getLowestFrequency();
    void updateBuffer();

protected:
    SampleType *buffer;
    std::size_t bufferSize;

private:
    // TODO Change function type
    std::vector<std::function<void()> > formula;
    uint16_t bitrate;
    bool changed;
    float lowestFreq;
};

#endif  // WAVE_H
