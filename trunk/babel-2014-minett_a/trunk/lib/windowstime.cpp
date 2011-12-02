#include "windowstime.h"
#ifdef OS_WINDOWS
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

struct timezone
{
  int  tz_minuteswest;
  int  tz_dsttime;
};

int gettimeofday(struct timeval *tv)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;

  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
    tmpres /= 10;
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
    tv->tv_sec = (unsigned int) (tmpres / 1000000UL);
    tv->tv_usec = (unsigned int) (tmpres % 1000000UL);
  }
  return 0;
}

Win32Time::Win32Time()
{
    this->_timems = 0;
}

void Win32Time::setToMsTimeOfDay()
{
    struct timeval t;

    ::gettimeofday(&t);
    _timems = t.tv_sec * 1000 + t.tv_usec / 10000;
}

ITime & Win32Time::operator- (ITime const &c) const
{
    Win32Time t;

    t.setMs(this->getMs() - c.getMs());
    return (t);
}

unsigned long long Win32Time::getMs() const
{
    return this->_timems;
}

void Win32Time::setMs(unsigned long long ms)
{
    this->_timems = ms;
}

#endif
