#ifndef NOTES_H
#define NOTES_H

#include <vector>
#include <cstdint>
#include "note.h"

class Notes
{
public:
    Notes();
    ~Notes();
    void addNote(uint8_t pitch, uint8_t velocity);
    void removeNote(uint8_t pitch);

private:
    std::vector<Note> notes;
}

#endif  // NOTES_H
