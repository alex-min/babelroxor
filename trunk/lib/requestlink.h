#ifndef REQUESTLINK_H
#define REQUESTLINK_H
#include "singleton.h"
#include "iportablesocket.h"

class RequestLink
{
public:
    RequestLink();
    void createNewLink(std::string const &login);
    bool createServerSock();

protected:
    PortableSocket _serverSock;
    bool           _testedServerSock;
    bool           _serverSockExist;
};

typedef Singleton<RequestLink> RequestLinkSingleton;

#endif // REQUESTLINK_H
