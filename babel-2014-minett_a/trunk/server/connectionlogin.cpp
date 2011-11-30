#include "connectionlogin.h"

ConnectionLogin::ConnectionLogin()
{
}

void ConnectionLogin::onCall(Network *network, const std::string &login,
                             void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || !data || !header)
        return ;
    // TODO do a real login function
    _s = Protocol::OK;
    std::string lg = AccountManager::dataTologin(data, len);
    std::cout << "CALLING CONNECTION with login " << lg << " and network=" << network << std::endl;

    Protocol::getInstance()->sendPacket(network, Protocol::STATUS, &_s, sizeof(Protocol::Status), header->_packetId, true);
    NetworkRouteSingleton::getInstance()->registerRoute(lg, network, false);
    AccountManager::getInstance()->setLoginToNetwork(network, lg);
}
