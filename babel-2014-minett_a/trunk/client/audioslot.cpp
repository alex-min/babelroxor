#include "audioslot.h"

AudioSlot::AudioSlot()
{
}

void AudioSlot::onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    //ici on lance le play()
    return ;
}
