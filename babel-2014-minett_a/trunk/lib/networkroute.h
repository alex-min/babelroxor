#ifndef NETWORKROUTE_H
#define NETWORKROUTE_H
#include <map>
#include <sstream>
#include "network.h"
#include "protocol.h"
#include "singleton.h"

typedef Singleton<NetworkRoute> NetworkRouteSingleton;

class NetworkRoute
{
public:
    void registerRoute(std::string const &login, Network *network, bool proxy);
    std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *getRouteFromLogin(std::string const &login);
    void eraseRoute(std::string const &login);
    std::string const &getIp() const;
    static std::string const &getIpFromLong(unsigned long ip);
    unsigned long getuIp() const;
    void setIp(unsigned long ip);
    static Protocol::Status sockTypeToStatus(IPortableSocket::SockType sock);
    static IPortableSocket::SockType statusToSockType(Protocol::Status s);

private:
    std::map<std::string, std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> > _proxyfiedArray;
    unsigned long _ip;
    std::string _sip;
    static std::string _tmpString;
};

#endif // NETWORKROUTE_H
