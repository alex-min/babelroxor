#ifndef PROXYSLOT_H
#define PROXYSLOT_H
#include "islotinterface.h"
#include "protocol.h"
#include "accountmanager.h"

class ProxySlot : public ISlotInterface
{
public:
    virtual void    onCall(Network *network, std::string const &login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);

};

#endif // PROXYSLOT_H
