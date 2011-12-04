#include "connecttome.h"
#include "accountmanager.h"

_ConnectToMe::_ConnectToMe()
{
}

void _ConnectToMe::sendConnnectToMe(std::string const &login, IPortableSocket::SockType type,
                      unsigned long ip, unsigned long port)
{
    Protocol::Status s = NetworkRoute::sockTypeToStatus(type);
    ::memcpy(_buf, &s, sizeof(Protocol::Status));
    ::memcpy(_buf + sizeof(Protocol::Status), &ip, sizeof(unsigned long));
    ::memcpy(_buf + sizeof(Protocol::Status) + sizeof(unsigned long), &port, sizeof(unsigned long));
    Protocol::getInstance()->send(login, Protocol::CONNECT_TO_ME,
                                  _buf, sizeof(Protocol::Status) + (sizeof(unsigned long) * 2), false);
}

void _ConnectToMe::onCall(Network *network, const std::string &login,
                          void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !data ||
            len < sizeof(Protocol::Status) + (sizeof(unsigned long) * 2) || !header)
        return ;
    Protocol::Status s = *reinterpret_cast<Protocol::Status *> (data);
    unsigned long ip = *reinterpret_cast<unsigned long *> (static_cast<char *> (data) + sizeof(Protocol::Status));
    unsigned long port = *reinterpret_cast<unsigned long *>
            (static_cast<char *> (data) + sizeof(Protocol::Status) + sizeof(unsigned long));

    PortableSocket *sock = new PortableSocket;

    std::cout << "ConnectToMe::connecting to " << NetworkRoute::getIpFromLong(ip) << ":" << port << std::endl;
    if (sock->connect(NetworkRoute::getIpFromLong(ip), port, NetworkRoute::statusToSockType(s)) == false)
    {
                 std::cout << "ConnectToMe::connectionFailed" << std::endl;
                 delete sock;
        // connection failed (could not happen).
        return ;
    }

    Network *net = new Network(sock);
    PortableNetworkManagerSingle::getInstance()->addNetwork(net);
    NetworkRouteSingleton::getInstance()->registerRoute(login, net, false);
}
