#ifndef AUDIOSLOT_H
#define AUDIOSLOT_H
#include "islotinterface.h"
#include "singleton.h"

class AudioSlot : public ISlotInterface
{
public:
    virtual void onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header);
    AudioSlot();
};

typedef Singleton<AudioSlot> AudioSlotSingle;

#endif // AUDIOSLOT_H
