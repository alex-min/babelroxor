#include "requestlink.h"
#include "connecttome.h"
#include "accountmanager.h"
#include "ListenServer.h"
#include "CentralWidget.h"
#ifdef OS_UNIX
#include <sys/time.h>
#include <unistd.h>
#endif

RequestLink::RequestLink()
{
    _testedServerSock = false;
    _serverSockExist = false;
    _net = new Network;
}

bool RequestLink::createServerSockMiam(std::string const &login)
{
  std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *route =
            NetworkRouteSingleton::getInstance()->getRouteFromLogin(login);
  if (route->second._slotType == Protocol::PROXY_DIRECT)
  {
      std::cout << "RequestLink::createSock:connection already set" << std::endl;
      unsigned int id = Protocol::getInstance()->getCurrentReplyId();
      Protocol::getInstance()->send(login, Protocol::CALL, "", 0, id, false);
      Protocol::getInstance()->registerPacketId(id, login,
                                                route->first, this,
                                                reinterpret_cast<Protocol::SlotCall> (&RequestLink::calling),
                                                login,
                                                20000);
  }
  else {
    _net->getSocket()->createServerSocket(IPortableSocket::TCP, 7536);
      PortableNetworkManagerSingle::getInstance()->addNetwork(_net);
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

void RequestLink::calling(bool timeout, Packet *p)
{
    std::cout << "RequestLink::calling: THIS FUNCTION IS THE GOAL OF THE PROJECT !! :P" << std::endl;
    if (timeout)
    {
        ListenServerSingleton::getInstance()->emitCallFail();
        return ;
    }
    if (p == NULL || p->getLogin() == "")
    {
        std::cerr << "RequestLink::calling something failed" << std::endl;
    }
    else {
      std::cout << "RequestLink::getInstance() : emit talk window" << std::endl;
     CentralWidgetSingleton::getInstance()->emitNeedOpenTalkWindow(p->getLogin().c_str());
    }
    //    emin callSuccess(login); //throw popup
}

bool RequestLink::createNewLink(std::string const &login)
{
    if (login == "")
        return (false);

   return (RequestLink::createServerSockMiam(login));
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
        _net->setName(p->getReturningLogin());
        ConnectToMe::getInstance()->sendConnnectToMe(p->getReturningLogin(),
                                                     _type,
                                                     NetworkRouteSingleton::getInstance()->getuIp(),
                                                     _port);
        unsigned int id = Protocol::getInstance()->getCurrentReplyId();
        Protocol::getInstance()->send(p->getReturningLogin(), Protocol::CALL, "", 0, id, false);
        std::cout << "registring id:" << id << std::endl;
        Protocol::getInstance()->registerPacketId(id, p->getReturningLogin(),
                                                  p->getNetwork(), this,
                                                  reinterpret_cast<Protocol::SlotCall> (&RequestLink::calling), p->getReturningLogin(),
                                                  20000);
    }

}

void    RequestLink::onCall(Network *network, std::string const &login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
}
