#include "audioslot.h"

AudioSlot::AudioSlot()
{
    _s.decoder = new DecoderSpeex;
    _s.encoder = new EncoderSpeex(5);
    _s.state = DECODING;
    _dec.setCallback(PortaudioWrapper::SpeexToSpeaker);
    _dec.openStream(0, 1, &_s, paInt16, _s.encoder->Rate(), _s.encoder->FrameSize());
}

void AudioSlot::onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header)
{
    //ici on decode le data apres l'avoir caster en char *, puis on joue.

    _s.buf = (char *)data;
    _s.size_encoded = 42;
//    _s.decoder = t->decoder;
//    _s.encoder = t->encoder;
    _s.state == DECODING;

    _dec.start();
    _dec.stop();
}
