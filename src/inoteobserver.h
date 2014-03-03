#ifndef INOTEOBSERVER_H
#define INOTEOBSERVER_H

#include <memory>
#include "note.h"

class INoteObservable;
typedef std::shared_ptr<INoteObservable> PNoteObservable;

class INoteObserver
{
public:
    virtual ~INoteObserver(){};
    virtual void noteAdded(const Note &note) = 0;
    virtual void noteRemoved(const Note &note) = 0;
    virtual void notify(const PNoteObservable &&subject) = 0;
};

typedef std::shared_ptr<INoteObserver> PNoteObserver;

#endif  // INOTEOBSERVER_H
