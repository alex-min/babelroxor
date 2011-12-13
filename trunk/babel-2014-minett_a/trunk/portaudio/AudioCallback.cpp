#include "AudioHandler.h"
#include "AudioCallback.h"
#include "audiothread.h"


using namespace Audio2;

int PortaudioWrapper::SendEncode(const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData)
{
	SpeexBuffer		*s = (SpeexBuffer *)userData;
	short			*tmp = new short[framesPerBuffer];
	short			*ib = (short *)inputBuffer;

	if (s->state == ENCODING)
	{
		for (unsigned int i = 0; i < framesPerBuffer; i++, ib++)
                {
                    tmp[i] = *ib;
                }
                //s->buf = new char[s->encoder->FrameSize() + 1];
		s->size_encoded = s->encoder->Encode(tmp, s->buf);
		delete tmp;

                std::list<std::string> const & loglist = AudioThreadSingleton::getInstance()->getLoginList();
                if (loglist.size() != 0)
                    {
                        for (std::list<std::string>::const_iterator it = loglist.begin(); it != loglist.end(); ++it)
                        {
                            Protocol::getInstance()->send((*it), Protocol::AUDIO, (void *)s->buf, s->size_encoded);
                        }
                    }
                AudioThreadSingleton::getInstance()->freeLoginList();
        }
	return (0);
}

int PortaudioWrapper::ReceiveDecode(const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
                                        const PaStreamCallbackTimeInfo*,
                                        PaStreamCallbackFlags,
					void *userData)
{
	SpeexBuffer		*s = (SpeexBuffer *)userData;
	short			*tmp;
	short			*ob = (short *)outputBuffer;

        if (s->state == DECODING)
        {
                tmp = s->decoder->Decode(s->buf, s->size_encoded);

		for (unsigned int i = 0; i < framesPerBuffer; i++, ob++)
		{
                    *ob = tmp[i];
		}
                //delete s->buf;
                s->state = ENCODING;
        }

	return (0);
}
