#ifndef IMIDISOURCE_H
#define IMIDISOURCE_H

#include <memory>
#include "notes.h"

class IMidiSource
{
public:
    virtual ~IMidiSource(){};
    virtual void run() = 0;
    virtual Notes getNotes() = 0;
};

typedef std::shared_ptr<IMidiSource> PMidiSource;

#endif  // IMIDISOURCE_H
