#ifndef WAVE_H
#define WAVE_H

#include <functional>
#include <vector>
#include <cstdint>

class Wave
{
public:
    Wave(uint16_t bitrate);
    virtual ~Wave(){};
    virtual uint16_t getNextSample() = 0;
    void setNewFormula(std::function<void()> func);
    void addToFormula(std::function<void()> func);
    void setLowestFrequency(float freq);
    float getLowestFrequency();
    void updateBuffer();

protected:
    uint16_t *buffer;
    std::size_t bufferSize;

private:
    // TODO Change function type
    std::vector<std::function<void()> > formula;
    uint16_t bitrate;
    bool changed;
    float lowestFreq;
};

#endif  // WAVE_H
