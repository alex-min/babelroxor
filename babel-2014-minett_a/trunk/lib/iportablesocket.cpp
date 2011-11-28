#include "iportablesocket.h"


bool APortableSocket::createServerSockFromRange(PortableSocket::SockType type, unsigned int begin, unsigned int end)
{
    if (begin > end)
        return (false);
    for (unsigned int i = begin; i <= end; ++i)
        if (this->createServerSocket(type, i))
            return (true);
    return (false);
}
