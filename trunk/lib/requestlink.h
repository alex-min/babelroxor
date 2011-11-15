#ifndef REQUESTLINK_H
#define REQUESTLINK_H
#include "singleton.h"
#include "iportablesocket.h"
#include "protocol.h"
#include "network.h"
#include "islotinterface.h"
#include <string>

class RequestLink : public ISlotInterface
{
public:
    RequestLink();
    void createNewLink(std::string const &login);
    bool createServerSock(std::string const &login);
    virtual void testConnection(bool timeout, unsigned int id, Network *network,
                                std::string const &login,
                                void *data, unsigned int len,
                                Protocol::NetworkPacket::NetworkHeader *header);
    virtual void    onCall(Network *network, std::string const &login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);

protected:
    Network        _net;
    bool           _testedServerSock;
    bool           _serverSockExist;
};

typedef Singleton<RequestLink> RequestLinkSingleton;

#endif // REQUESTLINK_H
