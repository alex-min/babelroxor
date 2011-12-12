#include "connectionslot.h"

ConnectionSlot::ConnectionSlot()
{
}

void    ConnectionSlot::onCall(Network *network, std::string const &, void *data, unsigned int len,
                               Protocol::NetworkPacket::NetworkHeader *)
{
    // TODO : create a real login function
    std::string from_login = AccountManager::dataTologin(data, len);

    std::cout << "connection requested from : " << from_login << std::endl;
    AccountManagerSingleton::getInstance()->setLoginToNetwork(network, from_login);
    NetworkRouteSingleton::getInstance()->registerRoute(from_login, network, false);
  //  RequestLinkSingleton::getInstance()->createServerSock("fff");
}
