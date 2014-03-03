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
    for(auto &note : notes) {
        if(note.getPitch() == pitch) {
            present = true;
            break;
        }
    }

    if(!present) {
        Note note(pitch, velocity);
        notes.push_back(note);

        for(auto &observer : observers) {
            observer->notify(PNoteObservable(this));
            observer->noteAdded(note);
        }
    }
}

void Notes::removeNote(uint8_t pitch)
{
    // As we're providing a lambda to filter out which Note objects should be
    // removed, we can do the observer notification here as well to avoid
    // looping over the notes twice.
    auto notifyingPredicate = [this, pitch](Note note) {
        if(note.getPitch() == pitch) {
            for(auto &observer : this->observers) {
                observer->notify(PNoteObservable(this));
                observer->noteRemoved(note);
            }

            return true;
        }
        return false;
    };

    notes.erase(std::remove_if(notes.begin(), notes.end(), notifyingPredicate),
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
