#ifndef TESTCONNECTION_H
#define TESTCONNECTION_H
#include "singleton.h"
#include "islotinterface.h"
#include "protocol.h"
#include "iportablesocket.h"
#include "network.h"

class TestConnection : public ISlotInterface
{
public:
    virtual void    onCall(Network *network, std::string const &login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);
};

typedef Singleton<TestConnection> TestConnectionSingleton;

#endif // TESTCONNECTION_H
