#ifndef DEBUGOBSERVER_H
#define DEBUGOBSERVER_H

#include "inoteobserver.h"
#include "note.h"

class DebugObserver : public INoteObserver
{
public:
    DebugObserver();
    ~DebugObserver();
	void noteAdded(const Note &note);
	void noteRemoved(const Note &note);
};

#endif  // DEBUGOBSERVER_H
