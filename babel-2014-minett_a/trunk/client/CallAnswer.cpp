#include "CallAnswer.h"
#include "ListenServer.h"
#include "audiothread.h"

CallAnswer::CallAnswer()
{
    _login = "";
}

void    CallAnswer::onCall(Network *network, const std::string &login, void *data,
                           unsigned int, Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !data || !header)
        return ;

    std::cout << "CallAnswer::onCall() : CALLING !!" << header->_packetId << std::endl;


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
