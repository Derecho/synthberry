#ifndef WAVE_H
#define WAVE_H

#include <functional>
#include <vector>
#include <cstdint>


/*! \brief Abstract class used for generating and storing wave buffers
 *
 * The abstract Wave class provides a generic approach to store waves. A Wave
 * represents the sound associated with a note being played, along with any
 * additional effects. IAudioOutput implementations deal with the abstract Wave,
 * leaving SynthModule classes with the flexibility of choosing or even
 * introducing their own subclasses of Wave.
 *
 * A sound is constructed by setting a formula that generates the data for the
 * wave. SynthModule classes can add more formulas to the initial one to apply
 * any required effects. These formulas are implemented as functions and are
 * called sequentially upon generation of the buffer.
 *
 * Wave needs to know the lowest frequency present in the sound to accommodate
 * for a buffer which can hold at least one full period.
 */
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
