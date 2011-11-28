#ifndef CONNECTTOME_H
#define CONNECTTOME_H
#include "protocol.h"
#include "iportablesocket.h"
#include "singleton.h"
#include "networkroute.h"
#include "inetworkmanager.h"

class _ConnectToMe : public ISlotInterface
{
public:
    _ConnectToMe();
    void sendConnnectToMe(std::string const &login, IPortableSocket::SockType type,
                          unsigned long ip, unsigned long port);
    void onCall(Network *network, const std::string &login, void *data,
                unsigned int len, Protocol::NetworkPacket::NetworkHeader *header);

private:
    char _buf[sizeof(IPortableSocket::SockType) + sizeof(unsigned long) * 2];
};

typedef Singleton<_ConnectToMe> ConnectToMe;

#endif // CONNECTTOME_H
