#include "proxyreceivedslot.h"

void    ProxyReceivedSlot::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || !data || len < sizeof(Protocol::NetworkPacket::NetworkHeader) + 1 || !header)
        return ;
    std::string login_to = AccountManager::dataTologin(data, len);
    Protocol::NetworkPacket::NetworkHeader *head =
            reinterpret_cast<Protocol::NetworkPacket::NetworkHeader *>(static_cast<char *>(data) + login_to.length() + 1);
    Protocol::getInstance()->dispatchPacket(NULL, login_to,
                             static_cast<char *> (data) + login.length() + sizeof(Protocol::NetworkPacket::NetworkHeader) + 1,
                             len - sizeof(Protocol::NetworkPacket::NetworkHeader) - login.length() - 1,
                             head);
}
