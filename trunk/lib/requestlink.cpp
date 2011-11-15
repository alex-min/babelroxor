#include "requestlink.h"

RequestLink::RequestLink()
{
    _testedServerSock = false;
    _serverSockExist = false;
}

bool RequestLink::createServerSock(std::string const &login)
{
    _net.getSocket()->createServerSocket(IPortableSocket::TCP, 7534);
    unsigned int id = Protocol::getInstance()->getCurrentReplyId();

}

void RequestLink::createNewLink(std::string const &login)
{
    if (login == "")
        return ;

}
