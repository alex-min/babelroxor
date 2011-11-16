#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <map>
#include <cstring>
#include <string>
#include "portablelibrary.h"
#include "circularbuffer.h"

class NetworkRoute;
class ISlotInterface;
class Network;
class Packet;



class Protocol
{
public:
    struct NetworkPacket
    {
        struct NetworkHeader
        {
            unsigned char _begin;
            unsigned char _slotType;
            unsigned short _packetId;
            unsigned short _len;
            unsigned short _checksum;
            unsigned short _checksumData;
        } PACKED;
        void *data;
    };
    typedef void (ISlotInterface::*SlotCall)(bool timeout, Packet *);
    typedef std::map<unsigned int, Packet *> IdPacketMap;

    enum SlotType {AUDIO, TEXT, STATUS, CONNECTION, REGISTER,
                   REMOVEACCOUNT, HANGUP,
                   PROXY_FORWARD, PROXY_RECEIVED,
                   PROXY_DIRECT,
                   TYPEERROR,
                   REQUEST_CONNECTION,
                   CONNECT_TO_ME,
                   TEST_CONNECTION};
    enum Status {ONLINE, OFFLINE, BUSY, ONCALL,
                 DISCONNECTED, NEED_REGISTRATION, INVALID_PACKET,
                 OK, FAILED, TCP, UDP};
    enum {DEFAULT_TIMEOUT = 1000};
    // send to use at outside class
    void send(std::string const &login,
              SlotType type,
              const void *data,
              unsigned int length
              );
    void send(std::string const &login,
              SlotType type,
              const void *data,
              unsigned int length,
              unsigned int packetReplyId
              );
    unsigned int getCurrentReplyId() const;
    void registerSlot(SlotType type, ISlotInterface *slot);
    void registerPacketId(unsigned short id, std::string const &login,
                          ISlotInterface *slot, SlotCall call, short timeout = -1);
    void unregisterPacket(unsigned short id, std::string const &login);
    void defaultGateway(Network *network);
    void readEvent(Network *network);
    void welcomeEvent(Network *network);
    static Protocol *getInstance();
    void sendPacket(Network *network, SlotType type, const void *data, unsigned int length);
    void sendPacket(Network *network, SlotType type, const void *data, unsigned int length, unsigned int packetId);
    void sendProxifiedPacket(Network *network, SlotType type, const void *data,
                             unsigned int length, std::string const &login, unsigned int packetId,
                             bool resend = false);
    void sendProxifiedPacket(Network *network, SlotType type, const void *data,
                             unsigned int length, std::string const &login, bool resend = false);
    void dispatchPacket(Network *network, std::string const &login, void *data, unsigned int len,
                        Protocol::NetworkPacket::NetworkHeader *header);

private:
    void onReceivePacket(CircularBuffer *buf, Network *n);


protected:
    Network                             *_defaultGateway;
    std::map<SlotType, ISlotInterface *> _slotManager;
    IdPacketMap                          _slotIdManager;
    ISlotInterface                       *_slotPacketId[65536];
    NetworkPacket::NetworkHeader                        _header;
    char                                *_buffer;
    static  int _packetCount;

private:
     Protocol();
     static Protocol *_protocol;
};

#endif // PROTOCOL_H
