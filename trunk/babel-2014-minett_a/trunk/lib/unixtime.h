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
    virtual ITime & operator- (ITime const &);
    virtual unsigned long long getMs() const;
    virtual void setMs(unsigned long long ms);
protected:
    unsigned long long _timems;
};

#endif
#endif // UNIXTIME_H
