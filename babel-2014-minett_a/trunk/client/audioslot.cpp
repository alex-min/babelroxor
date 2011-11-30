#include "audioslot.h"

AudioSlot::AudioSlot()
{
    _pa.init();
    _pa.setOutput();
}

void AudioSlot::onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    //ici on lance le play()
    //_pa.setFrames(//faire le decode de data
                  //);
    _pa.play();
    return ;
}
