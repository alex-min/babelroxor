#ifndef AUDIOSLOT_H
#define AUDIOSLOT_H

#include "islotinterface.h"
#include "singleton.h"
#include "portaudio.h"
#include "AudioCallback.h"
#include "AudioHandler.h"
#include "DecoderSpeex.h"
#include "EncoderSpeex.h"

#define ENCODING true
#define DECODING false

class AudioSlot : public ISlotInterface
{
public:
    virtual void onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header);
    AudioSlot();
    ~AudioSlot() {_dec.stop();}
    void pause();
    void resume();

private:
    PortaudioWrapper::AudioHandler	_dec;
    PortaudioWrapper::SpeexBuffer	_s;
    bool                                isStart;
};

typedef Singleton<AudioSlot> AudioSlotSingle;

#endif // AUDIOSLOT_H
