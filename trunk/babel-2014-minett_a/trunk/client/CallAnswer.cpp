#include "CallAnswer.h"
#include "ListenServer.h"

CallAnswer::CallAnswer()
{
    _login = "";
}

void    CallAnswer::onCall(Network *network, const std::string &login, void *data,
                           unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !data || len < 0 || !header)
        return ;

    std::cout << "CallAnswer::onCall() : CALLING !!" << std::endl;
    ListenServerSingleton::getInstance()->emitCall(login, header->_packetId);
}

std::string const &CallAnswer::getLogin()
{
    return (_login);
}

void              CallAnswer::resetLogin()
{
    _login = "";
}
