#include "proxyreceivedslot.h"

void    ProxyReceivedSlot::onCall(Network *network, std::string const &, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || !data || len < sizeof(Protocol::NetworkPacket::NetworkHeader) + 1 || !header)
        return ;
    std::string login_to = AccountManager::dataTologin(data, len);
    Protocol::NetworkPacket::NetworkHeader *head =
            reinterpret_cast<Protocol::NetworkPacket::NetworkHeader *>(static_cast<char *>(data) + login_to.length() + 1);
    std::cout << "PROXY_RECEIVED_SLOT:" << head->_len << std::endl;
    Protocol::getInstance()->dispatchPacket(network, login_to,
                             static_cast<char *> (data) + login_to.length() + sizeof(Protocol::NetworkPacket::NetworkHeader) + 1,
                             head->_len,
                             head);
}
