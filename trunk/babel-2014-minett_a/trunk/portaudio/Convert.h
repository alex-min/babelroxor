
#ifndef UTILS_CONVERT_H_
#define UTILS_CONVERT_H_

#include <sstream>
#include <math.h>

#include "Config.h"

#ifndef M_PI
#define M_PI 3.14
#endif

namespace Utils
{
    namespace Convert
    {
        inline double LINK_OPTION_UTILS DegToRad(double deg)           {return (deg*M_PI)/180.0;}
        inline double LINK_OPTION_UTILS RadToDeg(double rad)           {return (rad*180.0)/M_PI;}

        template <typename T>
        bool StringTo(const std::string &s, T &dest)
        {
            std::istringstream iss(s);
            return (iss >> dest != 0);
        }

        template <typename T>
        std::string ToString(const T &data)
        {
            std::ostringstream oss;
            oss << data;
            return oss.str();
        }
    }
}

#endif
