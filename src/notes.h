#ifndef NOTES_H
#define NOTES_H

#include <vector>
#include <cstdint>
#include "note.h"
#include "inoteobserver.h"

class Notes
{
public:
    Notes();
    ~Notes();
    void addNote(uint8_t pitch, uint8_t velocity);
    void removeNote(uint8_t pitch);
    const std::vector<Note> getNotes();
    void registerObserver(INoteObserver *observer);
    void removeObserver(INoteObserver *observer);

private:
    std::vector<Note> notes;
    std::vector<INoteObserver *> observers;
};

#endif  // NOTES_H
