#include "debugobserver.h"
#include "log.h"

DebugObserver::DebugObserver()
{
}

DebugObserver::~DebugObserver()
{
}

void DebugObserver::noteAdded(const Note &note)
{
	LOG("Note " << std::hex << (unsigned int)note.getPitch() << " added with "
            "velocity " << std::hex << (unsigned int)note.getVelocity());
}

void DebugObserver::noteRemoved(const Note &note)
{
	LOG("Note " << std::hex << (unsigned int)note.getPitch() << " removed");
}
