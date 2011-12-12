#ifndef CONNECTIONLOGIN_H
#define CONNECTIONLOGIN_H
#include "islotinterface.h"
#include "singleton.h"
#include "networkroute.h"
#include "accountmanager.h"

class ConnectionLogin : public ISlotInterface
{
public:
    ConnectionLogin();
    void onCall(Network *network, const std::string &, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header);
};

typedef Singleton<ConnectionLogin> ConnectionLoginSlot;

#endif // CONNECTIONLOGIN_H

