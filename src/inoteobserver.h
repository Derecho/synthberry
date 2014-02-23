#ifndef INOTEOBSERVER_H
#define INOTEOBSERVER_H

#include <memory>
#include "note.h"

class INoteObserver
{
public:
    virtual ~INoteObserver(){};
    virtual void noteAdded(const Note &note) = 0;
    virtual void noteRemoved(const Note &note) = 0;
};

typedef std::shared_ptr<INoteObserver> PNoteObserver;

#endif  // INOTEOBSERVER_H
