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

    if(!present) {
        Note note = Note(pitch, velocity);
        notes.push_back(note);

        for(PNoteObserver observer : observers)
            observer->noteAdded(note);
    }
}

void Notes::removeNote(uint8_t pitch)
{
    for(std::vector<Note>::iterator it = notes.begin(); it != notes.end(); ++it) {
        if((*it).getPitch() == pitch) {
            notes.erase(it);

            for(PNoteObserver observer : observers)
                observer->noteRemoved(*it);
        }
    }
}

const std::vector<Note> Notes::getNotes() const
{
    return notes;
}

void Notes::registerObserver(PNoteObserver observer)
{
    observers.push_back(observer);
}

void Notes::removeObserver(PNoteObserver observer)
{
    for(std::vector<PNoteObserver>::iterator it = observers.begin(); it !=
            observers.end(); ++it)
        if((*it) == observer)
            observers.erase(it);
}
