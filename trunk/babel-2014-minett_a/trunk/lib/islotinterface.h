#ifndef ISLOTINTERFACE_H
#define ISLOTINTERFACE_H
#include <string>
#include "protocol.h"

class Network;

class ISlotInterface
{
public:
    virtual void    onCall(Network *network, std::string const &login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header) {};
protected:
    Protocol::Status _s;

};

#endif // ISLOTINTERFACE_H
