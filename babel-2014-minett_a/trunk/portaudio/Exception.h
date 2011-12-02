
#ifndef UTILS_EXCEPTION_H_
#define UTILS_EXCEPTION_H_

#include <exception>
#include <string>

#include "Config.h"

namespace Utils
{
    class LINK_OPTION_UTILS Exception : public std::exception
    {
        public:
            Exception(const std::string &msg) throw()                           {_msg = msg;}
            Exception(const std::string &name, const std::string &msg) throw()  {_msg = name + ": " + msg;}
            virtual ~Exception() throw()                                        {};

            const char *what() const throw()                                    {return _msg.c_str();}

        private:
            std::string	_msg;
    };
}

#endif
