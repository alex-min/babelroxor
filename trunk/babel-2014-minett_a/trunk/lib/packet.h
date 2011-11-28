#ifndef PACKET_H
#define PACKET_H
#include "protocol.h"

class Packet
{
public:
    Packet(unsigned int id = 0,
           Network *network = NULL,
           std::string const &login = "",
           void *data = NULL,
           unsigned int len = 0,
           Protocol::NetworkPacket::NetworkHeader *head = NULL,
           int msTimeout = -1,
           ISlotInterface *interfacef = NULL,
           Protocol::SlotCall call = NULL);
    void setTimeout(int msTimeout);
    void setNetwork(Network *net);
    void setLogin(std::string const &login);
    void setData(void *data);
    void setLen(unsigned int len);
    void setHeader(Protocol::NetworkPacket::NetworkHeader *head);
    void setSlot(ISlotInterface *interfacef);
    void setSlotCall(Protocol::SlotCall call);
    void setId(unsigned int id);

    unsigned int getTimeout() const;
    Network *getNetwork() const;
    std::string const & getLogin() const;
    void *getData() const;
    unsigned int getLen() const;
    ISlotInterface *getSlot() const;
    Protocol::SlotCall getSlotCall() const;
    Protocol::Status getStatus() const;
    unsigned int getId() const;
    void erase();


protected:
    int _timeout;
    unsigned int _id;
    Network     *_net;
    std::string _login;
    void        *_data;
    unsigned int _len;
    Protocol::NetworkPacket::NetworkHeader *_head;
    ISlotInterface *_interface;
    Protocol::SlotCall _call;
};



#endif // PACKET_H
