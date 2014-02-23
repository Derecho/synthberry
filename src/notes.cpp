#include <algorithm>
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
        Note note(pitch, velocity);
        notes.push_back(note);

        for(auto observer : observers)
            observer->noteAdded(note);
    }
}

void Notes::removeNote(uint8_t pitch)
{
    auto pitchCompare = [pitch](Note x) { return x.getPitch() == pitch; };

    for(auto note : notes)
        if(pitchCompare(note))
            for(auto observer : observers)
                observer->noteRemoved(note);

    notes.erase(std::remove_if(notes.begin(), notes.end(), pitchCompare),
            notes.end());
}

const std::vector<Note> Notes::getNotes() const
{
    return notes;
}

void Notes::registerObserver(PNoteObserver &observer)
{
    observers.push_back(observer);
}

void Notes::removeObserver(PNoteObserver &observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer),
            observers.end());
}
