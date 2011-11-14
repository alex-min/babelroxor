#include "networkroute.h"


void NetworkRoute::registerRoute(std::string const &login, Network *network, bool proxy)
{
    Protocol::NetworkPacket::NetworkHeader packetProxyHeader;

    packetProxyHeader._begin = 0x7;
    if (proxy)
        packetProxyHeader._slotType = Protocol::PROXY_FORWARD;
    else
        packetProxyHeader._slotType = Protocol::PROXY_DIRECT;
    packetProxyHeader._len = 0;
    packetProxyHeader._packetId = 0x4242;
    packetProxyHeader._checksum = 0x4242;
    _proxyfiedArray[login] = std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> (network, packetProxyHeader);
}

std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *NetworkRoute::getRouteFromLogin(std::string const &login)
{
    if (_proxyfiedArray.find(login) == _proxyfiedArray.end())
        return (NULL);
    return (&_proxyfiedArray[login]);
}
