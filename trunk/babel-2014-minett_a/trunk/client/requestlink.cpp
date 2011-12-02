#include "requestlink.h"
#include "connecttome.h"
#include "accountmanager.h"
#include "ListenServer.h"

RequestLink::RequestLink()
{
    _testedServerSock = false;
    _serverSockExist = false;
    _net = new Network;
}

bool RequestLink::createServerSockMiam(std::string const &login)
{
  // std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *route =
    //        NetworkRouteSingleton::getInstance()->getRouteFromLogin(login);
    if (1)
    {
      _net->getSocket()->createServerSocket(IPortableSocket::TCP, 7536);
     _type = IPortableSocket::TCP;
     _port = 7536;
      short unsigned int id = Protocol::getInstance()->getCurrentReplyId();
     std::cout << "RequestLink::createServerSock() : id = " << id << std::endl;
     TestConnectionSingleton::getInstance()->send("", IPortableSocket::TCP, 7536, false);
     std::cout << "RequestLink::createServerSock() :: registring packet..." << std::endl;
     Protocol::getInstance()->registerPacketId(id, "", Protocol::getInstance()->getDefaultGetaway(),
                                              RequestLinkSingleton::getInstance(),
                                              reinterpret_cast<Protocol::SlotCall> (&RequestLink::testConnection),
                                              login,
                                              Protocol::DEFAULT_TIMEOUT);
     std::cout << "RequestLink::createServerSock() :: DONE..." << std::endl;
return (false);
    }

    return (true);
}

void RequestLink::calling(bool timeout, Packet *)
{
    std::cout << "RequestLink::calling: THIS FUNCTION IS THE GOAL OF THE PROJECT !! :P" << std::endl;
    if (timeout)
    {
        ListenServerSingleton::getInstance()->emitCallFail();
    }
//    emin callSuccess(login); //throw popup
}

bool RequestLink::createNewLink(std::string const &login)
{
    if (login == "")
        return (false);

    if (!_serverSockExist)
     return (RequestLink::createServerSockMiam(login));
    else
     {
       RequestLink::calling(false, NULL);
       return (false);
     }
  return (false);
}

void RequestLink::testConnection(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        std::cout << "RequestLink::testConnection() : no response from host timeout=" << timeout  << std::endl;
        Protocol::getInstance()->send(p->getLogin(), Protocol::REQUEST_CONNECTION, NULL, 0);
        return ;
    }
    _serverSockExist = true;
    std::cout << "here:RequestLink::testConnection();" << std::endl;
    std::cout << "RequestLink::testConnection() len = " << p->getLen() << std::endl;
    if (p->getData() != NULL && p->getLen() >= sizeof(Protocol::Status) + 4)
    {
        std::cout << "{<=>}" << "HELLO WORLD" << std::endl;
        NetworkRouteSingleton::getInstance()->setIp
                (*(reinterpret_cast<unsigned int *> (static_cast<char *> (p->getData()) + sizeof(Protocol::Status))));
        ConnectToMe::getInstance()->sendConnnectToMe(p->getReturningLogin(),
                                                     _type,
                                                     NetworkRouteSingleton::getInstance()->getuIp(),
                                                     _port);
        unsigned int id = Protocol::getInstance()->getCurrentReplyId();
        Protocol::getInstance()->send(p->getReturningLogin(), Protocol::CALL, "", 0);
        Protocol::getInstance()->registerPacketId(id, p->getReturningLogin(),
                                                  p->getNetwork(), this,
                                                  reinterpret_cast<Protocol::SlotCall> (&RequestLink::calling), p->getReturningLogin(),
                                                  Protocol::DEFAULT_TIMEOUT);
        PortableNetworkManagerSingle::getInstance()->addNetwork(_net);
    }

}

void    RequestLink::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
}
