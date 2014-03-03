#ifndef INOTEOBSERVABLE_H
#define INOTEOBSERVABLE_H

#include <memory>
#include "note.h"

class INoteObserver;
typedef std::shared_ptr<INoteObserver> PNoteObserver;

class INoteObservable
{
public:
    virtual ~INoteObservable(){};
    virtual const std::vector<Note> getNotes() const = 0;
    virtual void registerObserver(PNoteObserver &observer) = 0;
    virtual void removeObserver(PNoteObserver &observer) = 0;
};

typedef std::shared_ptr<INoteObservable> PNoteObservable;

#endif  // INOTEOBSERVABLE_H
