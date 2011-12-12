#ifndef ISLOTINTERFACE_H
#define ISLOTINTERFACE_H
#include <string>
#include "protocol.h"

class Network;

class ISlotInterface
{
public:
    virtual void    onCall(Network *, std::string const &, void *, unsigned int,
                           Protocol::NetworkPacket::NetworkHeader *) {};
protected:
    Protocol::Status _s;

};

#endif // ISLOTINTERFACE_H
