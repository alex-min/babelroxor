#ifndef CONNECTIONSLOT_H
#define CONNECTIONSLOT_H
#include "islotinterface.h"
#include "accountmanager.h"
#include "protocol.h"

class ConnectionSlot : public ISlotInterface
{
public:
    ConnectionSlot();
    virtual void    onCall(Network *network, const std::string &, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *);
};

#endif // CONNECTIONSLOT_H
