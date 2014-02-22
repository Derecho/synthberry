#include "notes.h"

Notes::Notes()
{
}

void Notes::addNote(uint8_t pitch, uint8_t velocity)
{
    bool present = false;
    for(Note note : notes)
        if(note.getPitch() == pitch)
            present = true;

    if(!present)
        notes.emplace_back(pitch, velocity);
}

void Notes::removeNote(uint8_t pitch)
{
    for(notes::const_iterator it = notes.begin(); it != notes.end(); ++it)
        if((*it).getPitch() == pitch)
            notes.erase(it);
}
