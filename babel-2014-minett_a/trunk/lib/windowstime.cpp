#include "windowstime.h"
#include <Windows.h>
#ifdef OS_WINDOWS

Win32Time::Win32Time()
{

}

void Win32Time::setToMsTimeOfDay()
{
}

ITime & Win32Time::operator- (ITime const &) const
{
}

unsigned int Win32Time::getMs() const
{
}

void Win32Time::setMs(unsigned int ms)
{
}

#endif
