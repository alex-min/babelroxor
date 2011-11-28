#include "unixtime.h"
#ifdef OS_UNIX

UNIXTime::UNIXTime()
{
    _timems = 0;
}

void UNIXTime::setToMsTimeOfDay()
{
    struct timeval t;

    ::gettimeofday(&t, NULL);
    _timems = t.tv_sec * 1000 + t.tv_usec / 100;
}

ITime &UNIXTime::operator- (ITime const &c) const
{
    UNIXTime t;
    t.setMs(this->getMs() - c.getMs());
    return (t);
}

unsigned int UNIXTime::getMs() const
{
    return (_timems);
}

void UNIXTime::setMs(unsigned int ms)
{
   _timems = ms;
}

#endif
