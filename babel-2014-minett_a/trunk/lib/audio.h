#ifndef AUDIO_H
#define AUDIO_H
#include <iostream>
#include "islotinterface.h"
#include "protocol.h"

class Audio : public ISlotInterface
{
public:
    Audio();
    virtual void    onCall(Network *, std::string const & login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *);
};

#endif // AUDIO_H
