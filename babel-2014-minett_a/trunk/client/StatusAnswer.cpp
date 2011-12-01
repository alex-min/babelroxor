#include "StatusAnswer.h"
#include "ListenServer.h"
#include "status.h"

StatusAnswer::StatusAnswer()
{

}

void    StatusAnswer::onCall(Network *network, std::string const & login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !data || len < sizeof(Protocol::Status) || !header)
        return ;

    Protocol::Status *stat = static_cast<Protocol::Status *>(data);

    ListenServerSingleton::getInstance()->emitContactStatusChanged(login, StatusSingleton::getInstance()->getClientStatusFromProtocolStatus(*stat));
}
