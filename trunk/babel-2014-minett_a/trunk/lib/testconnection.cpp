#include "testconnection.h"

void TestConnection::send(const std::string &login, IPortableSocket::SockType type, unsigned short port)
{

    Protocol::Status connectType = Protocol::sockTypeToStatus(type);
    ::memcpy(_data, &connectType, sizeof(Protocol::Status));
    ::memcpy(_data + sizeof(Protocol::Status), &port, sizeof(unsigned short));
    Protocol::getInstance()->send(login, Protocol::TEST_CONNECTION, _data, sizeof(Protocol::Status) + sizeof(unsigned short));
}

void TestConnection::send(const std::string &login, IPortableSocket::SockType type,
                          unsigned short port, unsigned int packetId)
{
    Protocol::Status connectType = Protocol::sockTypeToStatus(type);
    ::memcpy(_data, &connectType, sizeof(Protocol::Status));
    ::memcpy(_data + sizeof(Protocol::Status), &port, sizeof(unsigned short));
    Protocol::getInstance()->send(login, Protocol::TEST_CONNECTION, _data, sizeof(Protocol::Status) + sizeof(unsigned short), packetId);
}


void    TestConnection::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                               Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !header)
        return ;
    //PortableSocket sock;
    //sock.connect()
    if (len < sizeof(Protocol::Status) + sizeof(unsigned short))
        return ;
    Protocol::Status *stat = static_cast<Protocol::Status *> (data);
    const unsigned short port = *reinterpret_cast<const unsigned short *>
            (static_cast<const char *> (data) + sizeof(Protocol::Status));

    Protocol::Status sendStatus;
    PortableSocket sock;
    bool res = false;
    switch (*stat)
    {
        case Protocol::TCP:
        std::cout << "connecting to" << network->getSocket()->getIp() << ":" << port << std::endl;
        res = sock.connect(network->getSocket()->getIp(), port, IPortableSocket::TCP);
        break;
        case Protocol::UDP:
        res = sock.connect(network->getSocket()->getIp(), port, IPortableSocket::UDP);
        break;
        default:
        sendStatus = Protocol::FAILED;
        Protocol::getInstance()->send(login, Protocol::TEST_CONNECTION, &sendStatus, sizeof(Protocol::Status),
                                      header->_packetId);
        return ;
        break;
    }
    if (res)
    {
        sendStatus = Protocol::OK;
        sock.disconnect();
    }
    else
    {
        sendStatus = Protocol::FAILED;
    }
   Protocol::getInstance()->send(login, Protocol::TEST_CONNECTION, &sendStatus, sizeof(Protocol::Status), header->_packetId);
}
