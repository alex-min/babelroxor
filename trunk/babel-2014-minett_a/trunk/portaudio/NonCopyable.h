
#ifndef UTILS_NON_COPYABLE_H_
#define UTILS_NON_COPYABLE_H_

#include "Config.h"

namespace Utils
{
    class LINK_OPTION_UTILS NonCopyable
    {
        protected:
            NonCopyable() {}

        private:
            NonCopyable(const NonCopyable&);
            NonCopyable& operator =(const NonCopyable&);
    };
}

#endif
