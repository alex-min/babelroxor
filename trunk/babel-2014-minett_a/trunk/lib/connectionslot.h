#ifndef CONNECTIONSLOT_H
#define CONNECTIONSLOT_H
#include "islotinterface.h"
#include "accountmanager.h"
#include "protocol.h"

class ConnectionSlot : public ISlotInterface
{
public:
    ConnectionSlot();
    virtual void    onCall(Network *network, const std::string &login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);
};

#endif // CONNECTIONSLOT_H
