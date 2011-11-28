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

IPortableSocket::SockType NetworkRoute::statusToSockType(Protocol::Status s)
{
    IPortableSocket::SockType t;

    if (s == Protocol::UDP)
        return (IPortableSocket::UDP);
    return (IPortableSocket::TCP);
}


Protocol::Status NetworkRoute::sockTypeToStatus(IPortableSocket::SockType sock)
{
    if (sock == IPortableSocket::UDP)
        return (Protocol::UDP);
    return (Protocol::TCP);
}

unsigned long NetworkRoute::getuIp() const
{
    return (_ip);
}

std::string const &NetworkRoute::getIp() const
{
    return (_sip);
}


std::string const &NetworkRoute::getIpFromLong(unsigned long ip)
{
    std::ostringstream s;

    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[0])) << ".";
    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[1])) << ".";
    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[2])) << ".";
    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[3]));
    return (s.str());
}

void NetworkRoute::setIp(unsigned long ip)
{
    std::ostringstream s;

    _ip = ip;
    _sip = "";
    std::cout << "NetworkRoute::setIp();" << ip << std::endl;
    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[0])) << ".";
    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[1])) << ".";
    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[2])) << ".";
    s << static_cast<int>((reinterpret_cast<unsigned char *>(&ip)[3]));
    _sip = s.str();
}

std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *NetworkRoute::getRouteFromLogin(std::string const &login)
{
    if (_proxyfiedArray.find(login) == _proxyfiedArray.end())
        return (NULL);
    return (&_proxyfiedArray[login]);
}

void NetworkRoute::eraseRoute(std::string const &login)
{
    NetworkRoute::registerRoute(login, NULL, true);
}
