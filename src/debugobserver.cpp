#include "debugobserver.h"
#include "log.h"

DebugObserver::DebugObserver() :
	INoteObserver()
{
}

DebugObserver::~DebugObserver()
{
}

void DebugObserver::noteAdded(const Note &note)
{
	LOG("Note " << note.getPitch() << " added with velocity " <<
			note.getVelocity());
}

void DebugObserver::noteRemoved(const Note &note)
{
	LOG("Note " << note.getPitch() << "removed");
}
