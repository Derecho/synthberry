#ifndef IMIDISOURCE_H
#define IMIDISOURCE_H

class IMidiSource
{
    public:
        virtual ~IMidiSource {};
        virtual void run() = 0;
}

#endif  // IMIDISOURCE_H
