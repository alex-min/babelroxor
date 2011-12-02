#ifndef TESTCONNECTION_H
#define TESTCONNECTION_H
#include <cstring>
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
    void send(const std::string &login, IPortableSocket::SockType connectType, unsigned short port, unsigned int packetId);
    void send(const std::string &login, IPortableSocket::SockType connectType, unsigned short port);
    void sendConnectionStatus(const std::string &login, Protocol::Status stat, std::string const &ip);
    void sendConnectionStatus(const std::string &login, Protocol::Status stat, std::string const &ip, unsigned int packetId);
protected:
    unsigned char        _data[sizeof(Protocol::Status) + sizeof(unsigned short)];
};

typedef Singleton<TestConnection> TestConnectionSingleton;

#endif // TESTCONNECTION_H
