#ifndef PROXYRECEIVEDSLOT_H
#define PROXYRECEIVEDSLOT_H
#include "islotinterface.h"
#include "protocol.h"
#include "accountmanager.h"


class ProxyReceivedSlot : public ISlotInterface
{
public:

    virtual void    onCall(Network *network, std::string const &login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);

};

typedef Singleton<ProxyReceivedSlot> ProxyReceivedSlotSingleton;

#endif // PROXYRECEIVEDSLOT_H
