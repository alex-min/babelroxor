#ifndef UNIXTIME_H
#define UNIXTIME_H
#include "time.h"
#ifdef OS_UNIX
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

class UNIXTime : public ITime
{
public:
    UNIXTime();
    virtual void setToMsTimeOfDay();
    virtual ITime & operator- (ITime const &) const;
    virtual unsigned int getMs() const;
    virtual void setMs(unsigned int ms);
protected:
    unsigned int _timems;
};

#endif
#endif // UNIXTIME_H
