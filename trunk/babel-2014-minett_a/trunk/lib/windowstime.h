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
    virtual ITime & operator- (ITime const &) const;
    virtual unsigned int getMs() const;
    virtual void setMs(unsigned int ms);
protected:
    unsigned int _timems;
};

#endif
#endif // WINDOWSTIME_H
