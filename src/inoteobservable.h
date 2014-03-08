#ifndef INOTEOBSERVABLE_H
#define INOTEOBSERVABLE_H

#include <memory>
#include "note.h"

class INoteObserver;
using PNoteObserver = std::shared_ptr<INoteObserver>;

class INoteObservable
{
public:
    virtual ~INoteObservable(){};
    virtual const std::vector<Note> getNotes() const = 0;
    virtual void registerObserver(PNoteObserver &observer) = 0;
    virtual void removeObserver(PNoteObserver &observer) = 0;
};

using PNoteObservable = std::shared_ptr<INoteObservable>;

#endif  // INOTEOBSERVABLE_H
