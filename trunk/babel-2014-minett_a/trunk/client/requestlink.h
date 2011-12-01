#ifndef REQUESTLINK_H
#define REQUESTLINK_H
#include "singleton.h"
#include "iportablesocket.h"
#include "protocol.h"
#include "network.h"
#include "islotinterface.h"
#include "packet.h"
#include "testconnection.h"
#include "networkroute.h"
#include "inetworkmanager.h"
#include <string>

class RequestLink : public ISlotInterface
{
public:
    RequestLink();
    bool createNewLink(std::string const &login);
    bool createServerSockMiam(std::string const &login);
    virtual void testConnection(bool timeout, Packet *);
    virtual void    onCall(Network *network, std::string const &login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);
    virtual void calling(bool timeout, Packet *);

protected:
    char _____[50];
    Network        *_net;
    bool           _testedServerSock;
    bool           _serverSockExist;
    IPortableSocket::SockType _type;
    unsigned int   _port;
    char ____[50];
};

typedef Singleton<RequestLink> RequestLinkSingleton;

#endif // REQUESTLINK_H
