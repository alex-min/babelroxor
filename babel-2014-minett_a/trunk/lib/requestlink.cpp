#include "requestlink.h"

RequestLink::RequestLink()
{
    _testedServerSock = false;
    _serverSockExist = false;
}

bool RequestLink::createServerSock(std::string const &login)
{
    _net.getSocket()->createServerSocket(IPortableSocket::TCP, 7536);
    short unsigned int id = Protocol::getInstance()->getCurrentReplyId();
    std::cout << "RequestLink::createServerSock() : id = " << id << std::endl;
    TestConnectionSingleton::getInstance()->send(login, IPortableSocket::TCP, 7536, id);
    Protocol::getInstance()->registerPacketId(id, login, NULL,
                                              RequestLinkSingleton::getInstance(),
                                              reinterpret_cast<Protocol::SlotCall> (&RequestLink::testConnection),
                                              Protocol::DEFAULT_TIMEOUT);
}

void RequestLink::createNewLink(std::string const &login)
{
    if (login == "")
        return ;

}

void RequestLink::testConnection(bool timeout, Packet *p)
{
    if (timeout)
    {
        std::cout << "RequestLink::testConnection() : no response from host" << std::endl;
        return ;
    }
    p->getData();
    std::cout << "here:RequestLink::testConnection();" << std::endl;
}

void    RequestLink::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
}
