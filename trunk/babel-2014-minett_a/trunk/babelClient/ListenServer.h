#ifndef LISTENSERVER_H
#define LISTENSERVER_H

#include "singleton.h"
#include "Thread.h"
#include "iportablesocket.h"
#include "network.h"
#include "inetworkmanager.h"
#include "protocol.h"
#include "audio.h"
#include "connectionslot.h"
#include "proxyslot.h"
#include "testconnection.h"
#include "proxyreceivedslot.h"
#include "requestlink.h"
#include "pool.h"
#include "packet.h"
#include "timerpool.h"
#include "audioslot.h"
#include "connectionlogin.h"
#include "protocolinterfaceslot.h"
#include "StatusAnswer.h"

class ListenServer : public Thread
{
public:
    ListenServer();
    virtual void    run(void);
    virtual ~ListenServer();
private:
    PortableNetworkManager _networkManager;
    bool                   _connection;
};

typedef Singleton<ListenServer> ListenServerSingleton;

#endif // LISTENSERVER_H
