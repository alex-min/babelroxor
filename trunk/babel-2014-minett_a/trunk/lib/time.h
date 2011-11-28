#ifndef TIME_H
#define TIME_H
#include "portablelibrary.h"

class ITime
{
public:
    virtual void setToMsTimeOfDay() = 0;
    virtual ITime & operator- (ITime const &) const = 0;
    virtual unsigned int getMs() const = 0;
    virtual void setMs(unsigned int ms) = 0;
};

#ifdef OS_WINDOWS
#include "windowstime.h"
typedef class WindowsTime PortableTime;
#elif defined OS_UNIX
#include "unixtime.h"
typedef class UNIXTime PortableTime;
#endif

#endif // TIME_H
