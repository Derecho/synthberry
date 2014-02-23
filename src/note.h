#ifndef NOTE_H
#define NOTE_H

#include <cstdint>

class Note
{
public:
    Note(uint8_t pitch, uint8_t velocity);
    ~Note();
    uint8_t getPitch() const;
    uint8_t getVelocity() const;

private:
    uint8_t pitch;
    uint8_t velocity;
};

#endif  // NOTE_H
