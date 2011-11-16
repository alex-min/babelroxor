#include "protocol.h"
#include "networkroute.h"
#include "accountmanager.h"
#include "islotinterface.h"
#include "network.h"
#include "timerpool.h"
#include "pool.h"


int Protocol::_packetCount = 0;
Protocol *Protocol::_protocol = NULL;

Protocol::Protocol() :
    _defaultGateway(NULL),
    _buffer(new char[4096])
{
}

unsigned int Protocol::getCurrentReplyId() const
{
    return (_packetCount);
}

void Protocol::registerPacketId(unsigned short id, std::string const &login,
                      ISlotInterface *slot, Protocol::SlotCall call, short timeout)
{
    Packet *p = Pool(Packet)::getInstance()->generate();
    p->setLogin(login);
    p->setTimeout(timeout);
    p->setSlot(slot);
    p->setSlotCall(call);
    _slotIdManager[id] = p;
    TimerPoolSingleton::getInstance()->addToPool(p, timeout);
}

void Protocol::send(std::string const &login,
          SlotType type,
          const void *data,
          unsigned int length
          )
{
    Protocol::send(login, type, data, length, _packetCount);
    _packetCount++;
}

void Protocol::send(std::string const &login,
           SlotType type,
          const void *data,
          unsigned int length,
          unsigned int packetReplyId
          )
{
    if (!data)
        return ;
    std::cout << "login:" << std::endl;
    std::pair<Network *, Protocol::NetworkPacket::NetworkHeader> *route =
            NetworkRouteSingleton::getInstance()->getRouteFromLogin(login);

    if (route)
    {
        if (route->second._slotType == PROXY_DIRECT)
            Protocol::sendPacket(route->first, type, data, length, packetReplyId);
        else
           Protocol::sendProxifiedPacket(route->first, type, data, length, login, packetReplyId);
    }
    else if (_defaultGateway)
    {
        Protocol::sendProxifiedPacket(_defaultGateway, type, data, length, login, packetReplyId);
        NetworkRouteSingleton::getInstance()->registerRoute(login, _defaultGateway, true);
    }
    else
    {
        std::cerr << "No default route found !! Go fix the code !" << std::endl;
    }
}

void Protocol::defaultGateway(Network *network)
{
    _defaultGateway = network;
}

void Protocol::sendProxifiedPacket(Network *network, SlotType type, const void *data, unsigned int length,
                                   std::string const &login, bool resend)
{
    Protocol::sendProxifiedPacket(network, type, data, length, login, _packetCount, resend);
}

void Protocol::sendProxifiedPacket(Network *network, SlotType type, const void *data, unsigned int length,
                                   std::string const &login, unsigned int packetId, bool resend)
{
    NetworkPacket::NetworkHeader packetProxyHeader;
    NetworkPacket::NetworkHeader packet;

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
    packet._slotType = static_cast<int> (type);
    packet._len = length;
    packet._packetId = packetId;
    packet._checksum = 0x4242;
    //packet._checksum = CRC::getCRC16(&(packet), length);
    network->getWriteBuffer()->append(reinterpret_cast<char *>(&packetProxyHeader), sizeof(NetworkPacket::NetworkHeader));
    network->getWriteBuffer()->append(login.c_str(), login.length());
    network->getWriteBuffer()->append("", 1);
    network->getWriteBuffer()->append(reinterpret_cast<char *>(&packet), sizeof(NetworkPacket::NetworkHeader));
    network->getWriteBuffer()->append(data, length);
}


void Protocol::sendPacket(Network *network, SlotType type, const void *data, unsigned int length, unsigned int packetId)
{
    NetworkPacket::NetworkHeader packet;

    if (!network || !data)
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
    network->getWriteBuffer()->append(data, length);
    //PortableSocket::send(reinterpret_cast<char *>(&packet), length);
}

void Protocol::sendPacket(Network *network, SlotType type, const void *data, unsigned int length)
{
    Protocol::sendPacket(network, type, data, length, _packetCount);
}

void Protocol::registerSlot(SlotType type, ISlotInterface *slot)
{
    _slotManager[type] = slot;
}

void Protocol::readEvent(Network *network)
{
    if (!network)
        return ;
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

    size = _header._len + sizeof(Protocol::NetworkPacket::NetworkHeader);
    if (size < 4096)
        buf->extract(_buffer, size);
    else
    {
        size = 4096;
        buf->extract(_buffer, 4096);
    }
    std::cout << "header packetid: " << _header._packetId << std::endl;

    Protocol::dispatchPacket(net,
                             AccountManager::getInstance()->getLoginFromNetwork(net),
                             _buffer + sizeof(Protocol::NetworkPacket::NetworkHeader),
                             size - sizeof(Protocol::NetworkPacket::NetworkHeader),
                             &_header);
    Protocol::readEvent(net);
}

void Protocol::dispatchPacket(Network *network, const std::string &login, void *data,
                              unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    if (_slotManager.find(static_cast<SlotType>(header->_slotType)) != _slotManager.end())
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
   // Protocol::sendPacket(network, Protocol::AUDIO, "hello world", 11);
    Protocol::sendProxifiedPacket(network, AUDIO, "hello world", 11, "minett_a", false);
    //char *str = "minett_a\0password";
    //Protocol::sendPacket(network, Protocol::CONNECTION, str, 17);
}
