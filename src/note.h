#ifndef NOTE_H
#define NOTE_H

#include <cstdint>

class Note
{
public:
    Note(uint8_t pitch, uint8_t velocity);
    ~Note();
    uint8_t getPitch();
    uint8_t getVelocity();

private:
    uint8_t pitch;
    uint8_t velocity;
};

#endif  // NOTE_H
