#ifndef WAVE_H
#define WAVE_H

#include <functional>
#include <vector>
#include <cstdint>


template <class SampleType> class Wave
{
// FormulaFunction(*buffer, bufferSize, bitrate)
using FormulaFunction = std::function<void(SampleType*, std::size_t, uint16_t)>;

public:
    Wave(uint16_t bitrate);
    virtual ~Wave();
    virtual SampleType getNextSample() = 0;
    void setNewFormula(FormulaFunction func);
    void addToFormula(FormulaFunction func);
    void setLowestFrequency(float freq);
    float getLowestFrequency();
    void updateBuffer();

protected:
    SampleType *buffer;
    std::size_t bufferSize;

private:
    std::vector<FormulaFunction> formula;
    uint16_t bitrate;
    bool changed;
    float lowestFreq;
};

#endif  // WAVE_H
