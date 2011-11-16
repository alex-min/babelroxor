#include "requestlink.h"

RequestLink::RequestLink()
{
    _testedServerSock = false;
    _serverSockExist = false;
}

bool RequestLink::createServerSock(std::string const &login)
{
    std::cout << "miam" << std::endl;
    _net.getSocket()->createServerSocket(IPortableSocket::TCP, 7534);
    short unsigned int id = Protocol::getInstance()->getCurrentReplyId();
    Protocol::getInstance()->registerPacketId(id, login,
                                              RequestLinkSingleton::getInstance(),
                                              reinterpret_cast<Protocol::SlotCall> (&RequestLink::testConnection),
                                              Protocol::DEFAULT_TIMEOUT);
}

void RequestLink::createNewLink(std::string const &login)
{
    if (login == "")
        return ;

}

void RequestLink::testConnection(bool timeout, Packet *)
{
    if (timeout)
        return ;
std::cout << "hello world" << std::endl;
}

void    RequestLink::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
}
