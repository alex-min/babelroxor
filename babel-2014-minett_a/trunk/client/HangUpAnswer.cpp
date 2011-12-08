#include "HangUpAnswer.h"
#include "ListenServer.h"

HangUpAnswer::HangUpAnswer()
{

}

void    HangUpAnswer::onCall(Network *network, const std::string &login, void *data,
                           unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !data || len <= 0 || !header)
        return ;

    std::cout << "HangUpAnswer::onCall() : CALLING !!" << std::endl;
    AudioSlotSingle::getInstance()->pause();
    std::string contactLogin = AccountManager::dataTologin(data, len);

    AudioThreadSingleton::getInstance()->removeLogin(login);

    contactLogin.resize(len);

    ListenServerSingleton::getInstance()->emitHungUp(login);
}
