#include "notes.h"

Notes::Notes()
{
}

Notes::~Notes()
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
    for(std::vector<Note>::iterator it = notes.begin(); it != notes.end(); ++it)
        if((*it).getPitch() == pitch)
            notes.erase(it);
}

const std::vector<Note> Notes::getNotes()
{
    return notes;
}

void Notes::registerObserver(INoteObserver *observer)
{
    observers.push_back(observer);
}

void Notes::removeObserver(INoteObserver *observer)
{
    for(std::vector<INoteObserver *>::iterator it = observers.begin(); it !=
            observers.end(); ++it)
        if((*it) == observer)
            observers.erase(it);
}
