#include "packet.h"

unsigned int _timeout;
unsigned int _id;
Network     *_net;
std::string _login;
void        *_data;
unsigned int _len;
Protocol::NetworkPacket::NetworkHeader *_head;

Packet::Packet(unsigned int id,
               Network *network,
               const std::string &login,
               void *data,
               unsigned int len,
               Protocol::NetworkPacket::NetworkHeader *head,
               int msTimeout,
               ISlotInterface *interface,
               Protocol::SlotCall call) :
    _timeout(msTimeout),
    _id(id),
    _net(network),
    _login(login),
    _data(data),
    _len(len),
    _head(head),
    _interface(interface),
    _call(call)
{
}

void Packet::erase()
{
    _timeout = 0;
    _id = 0;
    _net = NULL;
    _login = "";
    _data = 0;
    _len = 0;
    _head = 0;
    _interface = NULL;
    _call = NULL;
}

void Packet::setTimeout(int msTimeout)
{
    _timeout = msTimeout;
}

void Packet::setNetwork(Network *net)
{
    _net = net;
}

void Packet::setLogin(std::string const &login)
{
    _login = login;
}

void Packet::setData(void *data)
{
    _data = data;
}

void Packet::setLen(unsigned int len)
{
    _len = len;
}

void Packet::setHeader(Protocol::NetworkPacket::NetworkHeader *head)
{
    _head = head;
}

void Packet::setSlot(ISlotInterface *interface)
{
    _interface = interface;
}

void Packet::setSlotCall(Protocol::SlotCall call)
{
    _call = call;
}

unsigned int Packet::getTimeout() const
{
    return (_timeout);
}

Network *Packet::getNetwork() const
{
    return (_net);
}

std::string const & Packet::getLogin() const
{
    return (_login);
}

void *Packet::getData() const
{
    return (_data);
}

unsigned int Packet::getLen() const
{
    return (_len);
}

ISlotInterface *Packet::getSlot() const
{
   return (_interface);
}

Protocol::SlotCall Packet::getSlotCall() const
{
    return (_call);
}
