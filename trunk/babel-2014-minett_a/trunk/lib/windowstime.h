#ifndef WINDOWSTIME_H
#define WINDOWSTIME_H
#include "time.h"
#ifdef OS_WINDOWS
#include <iostream>
#include <windows.h>

class Win32Time : public ITime
{
public:
    Win32Time();
    virtual void setToMsTimeOfDay();
    virtual unsigned long long getMs() const;
    virtual void setMs(unsigned long long ms);
protected:
    unsigned long long _timems;
};

#endif
#endif // WINDOWSTIME_H
