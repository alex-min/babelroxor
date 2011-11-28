#ifndef INETWORKMANAGER_H
#define INETWORKMANAGER_H
#include "portablelibrary.h"
#include <list>
#include "network.h"
#include "protocol.h"

class INetworkManager
{
public:
    virtual void addNetwork(Network *network) = 0;
    virtual void run(long uTimeout = -1) = 0;

protected:
    Protocol *_protocol;
};

#ifdef OS_WINDOWS
#include "windowsnetworkmanager.h"
typedef class Win32NetworkManager PortableNetworkManager;
#elif defined OS_UNIX
#include "unixnetworkmanager.h"
typedef class UNIXNetworkManager PortableNetworkManager;
#endif

typedef Singleton<PortableNetworkManager> PortableNetworkManagerSingle;

#endif // INETWORKMANAGER_H
