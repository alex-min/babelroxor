#include "connectionlogin.h"

ConnectionLogin::ConnectionLogin()
{
}

void ConnectionLogin::onCall(Network *network, const std::string &login,
                             void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || !data || !header)
        return ;

    std::string loginAccount = "";
    std::string passwordAccount = "";

    int i = 0;

    char *d = static_cast<char*>(data);

    for (; d[i]; ++i)
        loginAccount += d[i];

    if (i < len)
        ++i;

    for (; i < len; ++i)
        passwordAccount += d[i];

    std::cout << "CALLING CONNECTION with login " << loginAccount << " and network=" << network << std::endl;

    bool ret = true;

    ret = AccountManagerSingleton::getInstance()->checkIfAccountExist(loginAccount, passwordAccount);

    if (ret)
        _s = Protocol::OK;
    else
        _s = Protocol::FAILED;

    Protocol::getInstance()->sendPacket(network, Protocol::STATUS, &_s, sizeof(Protocol::Status), header->_packetId, true);
    NetworkRouteSingleton::getInstance()->registerRoute(loginAccount, network, false);
    AccountManagerSingleton::getInstance()->setLoginToNetwork(network, loginAccount);
}
