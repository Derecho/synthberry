#ifndef INOTEOBSERVER_H
#define INOTEOBSERVER_H

#include "note.h"

class INoteObserver
{
public:
    virtual ~INoteObserver(){};
    virtual void noteAdded(const Note &note) = 0;
    virtual void noteRemoved(const Note &note) = 0;
};

#endif  // INOTEOBSERVER_H
