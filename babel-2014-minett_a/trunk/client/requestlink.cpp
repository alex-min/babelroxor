#include "requestlink.h"
#include "connecttome.h"

RequestLink::RequestLink()
{
    _testedServerSock = false;
    _serverSockExist = false;
}

bool RequestLink::createServerSock(std::string const &login)
{
    _net.getSocket()->createServerSocket(IPortableSocket::TCP, 7536);
    _type = IPortableSocket::TCP;
    _port = 7536;
    short unsigned int id = Protocol::getInstance()->getCurrentReplyId();
    std::cout << "RequestLink::createServerSock() : id = " << id << std::endl;
    TestConnectionSingleton::getInstance()->send(login, IPortableSocket::TCP, 7536, false);
    Protocol::getInstance()->registerPacketId(id, login, Protocol::getInstance()->getDefaultGetaway(),
                                              RequestLinkSingleton::getInstance(),
                                              reinterpret_cast<Protocol::SlotCall> (&RequestLink::testConnection),
                                              Protocol::DEFAULT_TIMEOUT);
}

void RequestLink::createNewLink(std::string const &login)
{
    if (login == "")
        return ;
   std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *p =
           NetworkRouteSingleton::getInstance()->getRouteFromLogin(login);
   if (!p)
   {
        RequestLink::createServerSock(login);
   }
   else
   {

       std::cout << "RequestLink::createNewLink(): route already created" << std::endl;
   }
}

void RequestLink::testConnection(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        std::cout << "RequestLink::testConnection() : no response from host" << std::endl;
        Protocol::getInstance()->send(p->getLogin(), Protocol::REQUEST_CONNECTION, NULL, 0);
        return ;
    }
    std::cout << "here:RequestLink::testConnection();" << std::endl;
    if (p->getData() != NULL && p->getLen() >= sizeof(Protocol::Status) + 4)
    {
        std::cout << "{<=>}" << "HELLO WORLD" << std::endl;
        NetworkRouteSingleton::getInstance()->setIp
                (*(reinterpret_cast<unsigned int *> (static_cast<char *> (p->getData()) + sizeof(Protocol::Status))));
        ConnectToMe::getInstance()->sendConnnectToMe(p->getLogin(),
                                                     _type,
                                                     NetworkRouteSingleton::getInstance()->getuIp(),
                                                     _port);
    }

}

void    RequestLink::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
}
