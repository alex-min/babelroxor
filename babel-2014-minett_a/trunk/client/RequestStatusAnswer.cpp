#include "RequestStatusAnswer.h"
#include "ListenServer.h"
#include "status.h"

RequestStatusAnswer::RequestStatusAnswer()
{

}

void    RequestStatusAnswer::onCall(Network *network, std::string const & login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
    (void)data;
    (void)header;
    len = len;

    if (!network || login == "")
        return ;

    std::cout << "REQUEST STATUS ANSWER" << std::endl;

    ListenServerSingleton::getInstance()->emitAddContactToUpdateList(login);
    StatusSingleton::getInstance()->updateStatus(login);
}
