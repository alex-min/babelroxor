#include "audioslot.h"
#include "audiothread.h"

AudioSlot::AudioSlot()
{
    _s.decoder = new DecoderSpeex;
    _s.encoder = new EncoderSpeex(5);
    _s.state = true;
    _s.buf = new char[4000];
    _dec.setCallback(PortaudioWrapper::ReceiveDecode);
    _dec.openStream(0, 1, &_s, paInt16, _s.encoder->Rate(), _s.encoder->FrameSize());
    _dec.start();
    isStart = true;
}

void AudioSlot::pause()
{
    _dec.stop();
}

void AudioSlot::resume()
{
   _dec.start();
}

void AudioSlot::onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    //std::cout << "AUDIOSLOT POWAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
    //ici on decode le data apres l'avoir caster en char *, puis on joue.
    _s.buf = (char *)data;
    _s.size_encoded = len;
    _s.state = DECODING;
    AudioSlot::resume();
}
