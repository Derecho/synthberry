#include "note.h"

Note::Note(uint8_t pitch, uint8_t velocity) :
    pitch(pitch),
    velocity(velocity)
{
}

Note::~Note()
{
}

uint8_t Note::getPitch() const
{
    return pitch;
}

uint8_t Note::getVelocity() const
{
    return velocity;
}
