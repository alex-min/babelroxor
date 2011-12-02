#include "unixtime.h"
#include <iostream>

#ifdef OS_UNIX

UNIXTime::UNIXTime()
{
    _timems = 0;
}

void UNIXTime::setToMsTimeOfDay()
{
    struct timeval t;

    ::gettimeofday(&t, NULL);
    _timems = t.tv_sec * 1000 + t.tv_usec / 10000;
    //std::cout << "Timems : " << _timems << std::endl;
}

ITime &UNIXTime::operator- (ITime const &c) const
{
    UNIXTime t;
    t.setMs(this->getMs() - c.getMs());
    return (t);
}

unsigned long long UNIXTime::getMs() const
{
    return (_timems);
}

void UNIXTime::setMs(unsigned long long ms)
{
   _timems = ms;
}

#endif
