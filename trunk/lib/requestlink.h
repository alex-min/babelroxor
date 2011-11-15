#ifndef REQUESTLINK_H
#define REQUESTLINK_H
#include "singleton.h"
#include "iportablesocket.h"
#include "protocol.h"
#include "network.h"

class RequestLink : public ISlotInterface
{
public:
    RequestLink();
    void createNewLink(std::string const &login);
    bool createServerSock(std::string const &login);


protected:
    Network        _net;
    bool           _testedServerSock;
    bool           _serverSockExist;
};

typedef Singleton<RequestLink> RequestLinkSingleton;

#endif // REQUESTLINK_H
