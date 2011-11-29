#ifndef PROTOCOLINTERFACESLOT_H
#define PROTOCOLINTERFACESLOT_H
#include <string>
#include "protocol.h"
#include "singleton.h"
#include "islotinterface.h"
#include "packet.h"

class _ProtocolInterfaceSlot : public ISlotInterface
{
public:
    _ProtocolInterfaceSlot();
    void loginSlot(bool, Packet *);
    void registerSlot(bool, Packet*);
};

typedef Singleton<_ProtocolInterfaceSlot> ProtocolInterfaceSlot;

#endif // PROTOCOLINTERFACESLOT_H
