
#ifndef UTILS_CLOCK_H_
#define UTILS_CLOCK_H_

#include <iostream>
#include <string.h>
#include <sys/timeb.h>

#include "SystemAPI.h"

namespace Utils
{
    class LINK_OPTION_UTILS Clock
    {
        public:
            Clock()	    {Reset();}
			~Clock()	{};

            friend std::ostream &operator << (std::ostream &os, const Clock &cl)
            {
                os << "time = " << cl.ElapsedTime() << "s";
                return os;
            }

            inline void Reset()                     {_startTime = _stopTime = 0;}
            inline void	Start()						{_startTime = System::Time();}
            inline void	Stop()						{_stopTime = System::Time();}
            inline double ElapsedTime() const       {return _stopTime - _startTime;}

        private:
            double  _startTime;
            double  _stopTime;
    };
}

#endif
