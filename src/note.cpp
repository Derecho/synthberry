#include "note.h"

Note::Note(uint8_t pitch, uint8_t velocity) :
    pitch(pitch),
    velocity(velocity)
{
}

uint8_t Note::getPitch()
{
    return pitch;
}

uint8_t Note::getVelocity()
{
    return velocity;
}
