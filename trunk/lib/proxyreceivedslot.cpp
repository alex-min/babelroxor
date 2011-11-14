#include "proxyreceivedslot.h"

void    ProxyReceivedSlot::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !data || len < sizeof(Protocol::NetworkPacket::NetworkHeader) + 1 || !header)
        return ;

}
