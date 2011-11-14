#ifndef NETWORKROUTE_H
#define NETWORKROUTE_H
#include <map>
#include "network.h"
#include "protocol.h"
#include "singleton.h"

typedef Singleton<NetworkRoute> NetworkRouteSingleton;

class NetworkRoute
{
public:
    void registerRoute(std::string const &login, Network *network, bool proxy);
    std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *getRouteFromLogin(std::string const &login);

private:
    std::map<std::string, std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> > _proxyfiedArray;
};

#endif // NETWORKROUTE_H
