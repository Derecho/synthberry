#ifndef IMIDISOURCE_H
#define IMIDISOURCE_H

#include <memory>
#include "notes.h"

class IMidiSource
{
public:
    virtual ~IMidiSource(){};
    virtual void run() = 0;
    virtual Notes& getNotes() = 0;
};

using PMidiSource = std::shared_ptr<IMidiSource>;

#endif  // IMIDISOURCE_H
