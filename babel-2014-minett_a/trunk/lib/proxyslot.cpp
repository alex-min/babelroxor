#include "proxyslot.h"

void    ProxySlot::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                          Protocol::NetworkPacket::NetworkHeader *header)
{
    Protocol::Status status;
    std::string destination;
    if (!network)
        return ;
    if (login == "")
    {
        status = Protocol::FAILED;
        Protocol::getInstance()->sendPacket(network, Protocol::STATUS, &status, sizeof(Protocol::Status));
        std::cout << "[proxy] need registration" << std::endl;
        return ;
    }
    Network *net = AccountManagerSingleton::getInstance()->getNetworkFromLogin(data, len);
    if (!net)
    {
        status = Protocol::FAILED;
        Protocol::getInstance()->sendPacket(network, Protocol::STATUS, &status, sizeof(Protocol::Status));
        std::cout << "[proxy]" << AccountManager::dataTologin(data, len) << " may not be connected" << std::endl;
        return ;
    }
        //Protocol::sendProxifiedPacket(network, )
    std::string login_to = AccountManager::dataTologin(data, len);
    if (login_to != "" && len - login_to.length() > 8)
    {
       const Protocol::NetworkPacket::NetworkHeader *head =
        reinterpret_cast<const Protocol::NetworkPacket::NetworkHeader *> (static_cast<const char *>(data) + login_to.length() + 1);
       std::cout << "ProxySlot::onCall() : Sending proxified packet" << std::endl;
       Protocol::getInstance()->sendProxifiedPacket(
                                      AccountManagerSingleton::getInstance()->getNetworkFromLogin(login_to),
                                      static_cast<Protocol::SlotType> (head->_slotType),
                    static_cast<const char *> (data)
          + login_to.length() + sizeof(Protocol::NetworkPacket::NetworkHeader) + 1,
                                      len - sizeof(Protocol::NetworkPacket::NetworkHeader)
                                      - login_to.length() - 1,
                                      login,
                                      true
                                      );
    }
}
