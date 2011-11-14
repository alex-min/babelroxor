#include "requestlink.h"

RequestLink::RequestLink()
{
    _testedServerSock = false;
    _serverSockExist = false;
}

bool RequestLink::createServerSock()
{

}

void RequestLink::createNewLink(std::string const &login)
{
    if (login == "")
        return ;

}
