#include "protocol.h"
#include "networkroute.h"
#include "accountmanager.h"
#include "islotinterface.h"
#include "network.h"
#include "timerpool.h"
#include "pool.h"
#include "proxyreceivedslot.h"


int Protocol::_packetCount = 0;
Protocol *Protocol::_protocol = NULL;

Protocol::Protocol() :
    _defaultGateway(NULL),
    _buffer(new char[4096])
{
    _m.create();
}

Network *Protocol::getDefaultGetaway() const
{
    return (_defaultGateway);
}

unsigned int Protocol::getCurrentReplyId() const
{
    ScopedLock s(const_cast<Mutex *> (&_m));

    return (_packetCount);
}

Protocol::Status Protocol::sockTypeToStatus(IPortableSocket::SockType const & type)
{
    Protocol::Status ret;

    switch (type)
    {
        case IPortableSocket::UDP:
            ret = Protocol::UDP;
            break;
        default:
            ret = Protocol::TCP;
        break;
    }
    return (ret);
}


void Protocol::registerPacketId(unsigned short id, std::string const &login, Network *net,
                      ISlotInterface *slot, Protocol::SlotCall call, short timeout)
{
    ScopedLock s(&_m);

    Packet *p = Pool(Packet)::getInstance()->generate();
    p->setLogin(login);
    p->setTimeout(timeout);
    p->setSlot(slot);
    p->setSlotCall(call);
    p->setId(id);
    p->setNetwork(net);
    _slotIdManager.push_front(p);
    TimerPoolSingleton::getInstance()->addToPool(p, timeout);
}

void Protocol::unregisterPacket(unsigned short id, std::string const &login)

{
    ScopedLock s(&_m);

   for (IdPacketMap::iterator it = _slotIdManager.begin(); it != _slotIdManager.end(); ++it)
   {
       if ((*it)->getId() == id && (*it)->getLogin() == login)
       {
           _slotIdManager.erase(it);
           return ;
       }
   }
}


void Protocol::send(std::string const &login,
           SlotType type,
          const void *data,
          unsigned int length,
          bool mutex)
{

    Protocol::send(login, type, data, length, _packetCount, mutex);
}

void Protocol::send(std::string const &login,
           SlotType type,
          const void *data,
          unsigned int length,
          unsigned int packetReplyId,
          bool mutex)
{

    if (!data)
        return ;
    std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *route =
            NetworkRouteSingleton::getInstance()->getRouteFromLogin(login);
    std::cout << "Protocol::Send : Route found from login : " << route << std::endl;

    if (route && login != "")
    {
        if (route->second._slotType == PROXY_DIRECT)
            Protocol::sendPacket(route->first, type, data, length, packetReplyId, mutex);
        else
           Protocol::sendProxifiedPacket(route->first, type, data, length, login, packetReplyId, false, mutex);
    }
    else if (_defaultGateway)
    {
        if (login == "")
        {
            std::cout << "Send by gateway" << std::endl;
            Protocol::sendPacket(_defaultGateway, type, data, length, packetReplyId, mutex);
        }
        else
        {
            std::cout << "Send by PROXY (type=" << type << ") data=(" << data << ") length=(" << length << std::endl;
            std::cout << "login=" << login << " mutex="  << mutex << std::endl;
            Protocol::sendProxifiedPacket(_defaultGateway, type, data, length, login, packetReplyId, false, mutex);
            NetworkRouteSingleton::getInstance()->registerRoute(login, _defaultGateway, true);
        }
    }
    else
    {
        std::cerr << "No default route found !! Go fix the code !" << std::endl;
    }
}

void Protocol::defaultGateway(Network *network)
{
    ScopedLock s(&_m);

    _defaultGateway = network;
}

void Protocol::sendProxifiedPacket(Network *network, SlotType type, const void *data, unsigned int length,
                                   std::string const &login, bool resend, bool mutex)
{
    Protocol::sendProxifiedPacket(network, type, data, length, login, _packetCount, resend, mutex);
}

void Protocol::sendProxifiedPacket(Network *network, SlotType type, const void *data, unsigned int length,
                                   std::string const &login, unsigned int packetId, bool resend,  bool mutex)
{
    NetworkPacket::NetworkHeader packetProxyHeader;
    NetworkPacket::NetworkHeader packet;
    std::cout << mutex << std::endl;
    ScopedLock s(&_m);


    if (!network || !data)
          return ;

    ::memset(&packet, 0, sizeof(NetworkPacket::NetworkHeader));
    packetProxyHeader._begin = 0x7;
    if (!resend)
        packetProxyHeader._slotType = Protocol::PROXY_FORWARD;
    else
        packetProxyHeader._slotType = Protocol::PROXY_RECEIVED;
    packetProxyHeader._len = length + sizeof(NetworkPacket::NetworkHeader) + login.length() + 1;
    packetProxyHeader._packetId = packetId;
    packetProxyHeader._checksum = 0x4242;
    packet._begin = 0x7;
    std::cout << "Send Proxified with " << type << std::endl;
    packet._slotType = static_cast<char> (type);
    packet._len = length;
    packet._packetId = packetId;
    packet._checksum = 0x4242;
    //packet._checksum = CRC::getCRC16(&(packet), length);
    std::cout << "Test::::" << network->getSocket()->isServerSock() << std::endl;
    network->getWriteBuffer()->append(reinterpret_cast<char *>(&packetProxyHeader), sizeof(NetworkPacket::NetworkHeader));
    network->getWriteBuffer()->append(login.c_str(), login.length());
    network->getWriteBuffer()->append("", 1);
    network->getWriteBuffer()->append(reinterpret_cast<char *>(&packet), sizeof(NetworkPacket::NetworkHeader));
    if (data)
        network->getWriteBuffer()->append(data, length);
    std::cout << "Protocol::Network->getWriteBufferSize(=>" << network->getWriteBuffer()->getReadSize() << std::endl;
}



void Protocol::sendPacket(Network *network, SlotType type, const void *data, unsigned int length, unsigned int packetId, bool mutex)
{
    NetworkPacket::NetworkHeader packet;
    std::cout << "Protocol::sendPacket() : net:" << network << std::endl;
    ScopedLock s(&_m);
    if (!network)
          return ;
    ::memset(&packet, 0, sizeof(NetworkPacket::NetworkHeader));
    packet._begin = 0x7;
    packet._slotType = static_cast<int> (type);
    packet._len = length;
    packet._packetId = packetId;
    packet._checksum = 0x4242;
    packet._checksumData = 0x4242;
    //packet._checksum = CRC::getCRC16(&(packet), length);
    network->getWriteBuffer()->append(reinterpret_cast<char *>(&packet), sizeof(NetworkPacket::NetworkHeader));
    if (data)
    network->getWriteBuffer()->append(data, length);
    //PortableSocket::send(reinterpret_cast<char *>(&packet), length);
}

void Protocol::sendPacket(Network *network, SlotType type, const void *data, unsigned int length, bool mutex)
{
    Protocol::sendPacket(network, type, data, length, _packetCount, mutex);
}

void Protocol::registerSlot(SlotType type, ISlotInterface *slot)
{
    ScopedLock s(&_m);

    _slotManager[type] = slot;
}

void Protocol::readEvent(Network *network)
{
    if (!network)
        return ;
    std::cout << "Protocol::readEvent() (" <<  network->getReadBuffer()->getReadSize() << std::endl;
    // not enough for the network header
    if (network->getReadBuffer()->getReadSize() < sizeof(Protocol::NetworkPacket::NetworkHeader))
        return ;
    network->getReadBuffer()->extractKeep(&_header, sizeof(Protocol::NetworkPacket::NetworkHeader));
    // packet not received
    if (network->getReadBuffer()->getReadSize() < _header._len + sizeof(Protocol::NetworkPacket::NetworkHeader))
        return ;
    Protocol::onReceivePacket(network->getReadBuffer(), network);
}
void Protocol::onReceivePacket(CircularBuffer *buf, Network *net)
{

    unsigned int size;

    std::cout << "Protocol::onReceivePacket()" << std::endl;
    size = _header._len + sizeof(Protocol::NetworkPacket::NetworkHeader);
    if (size < 4096)
        buf->extract(_buffer, size);
    else
    {
        size = 4096;
        buf->extract(_buffer, 4096);
    }

    Protocol::dispatchPacket(net,
                             AccountManagerSingleton::getInstance()->getLoginFromNetwork(net),
                             _buffer + sizeof(Protocol::NetworkPacket::NetworkHeader),
                             _header._len,
                             &_header);
    Protocol::readEvent(net);
}

Packet *Protocol::getPacket(unsigned int id, std::string const & login, Network *net)
{
    for (Protocol::IdPacketMap::iterator it = _slotIdManager.begin();
         it != _slotIdManager.end(); ++it)
    {
        if (login == "" && net != NULL && (*it)->getNetwork() == net)
        {
            return (*it);
        }
        else if ((*it)->getLogin() == login && (*it)->getId() == id)
        {
                return (*it);
        }
    }
    return (NULL);
}


void Protocol::dispatchPacket(Network *network, const std::string &login, void *data,
                              unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{

    std::cout << "OnDispatch:" << (int) header->_slotType << std::endl;
    if (header && header->_slotType == PROXY_RECEIVED)
    {
        ProxyReceivedSlotSingleton::getInstance()->onCall(network, login, data, len, header);
        return ;
    }
    Packet *p = 0;

    if (header)
    p = Protocol::getInstance()->getPacket(header->_packetId, login, network);
    if (header && p)
    {
        p->setData(data);
        p->setLen(len);
            if (p->getSlot() && p->getSlotCall())
                (p->getSlot()->*p->getSlotCall())(false, p);
            Protocol::getInstance()->unregisterPacket(p->getId(), p->getLogin());
            TimerPoolSingleton::getInstance()->removeFromPool(p);
            Pool(Packet)::getInstance()->invalidate(p);
    }
    else if (_slotManager.find(static_cast<SlotType>(header->_slotType)) != _slotManager.end())
        _slotManager[static_cast<SlotType>(header->_slotType)]->onCall(network,
                                                                       login,
                                                                       data,
                                                                       len,
                                                                       header);
}

Protocol *Protocol::getInstance()
{
    if (!_protocol)
        _protocol = new Protocol;
    return (_protocol);
}

void Protocol::welcomeEvent(Network *network)
{
    std::cout << "New client connected" << std::endl;
   // Protocol::sendPacket(network, Protocol::AUDIO, "hello world", 11);
    //Protocol::sendProxifiedPacket(network, AUDIO, "hello world", 11, "minett_a", false);
    //char *str = "minett_a\0password";
    //Protocol::sendPacket(network, Protocol::CONNECTION, str, 17);
}
