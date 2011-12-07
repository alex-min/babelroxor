#include "AudioHandler.h"
#include "AudioCallback.h"
#include "audiothread.h"


using namespace Audio2;
using namespace PortaudioWrapper;
int grooo = 0;

int	PortaudioWrapper::MicroToSpeaker(const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData)
{
    (void)userData;
    (void)statusFlags;
    (void)timeInfo;
    short *ib = (short *)inputBuffer;
    short *ob = (short *)outputBuffer;
    
    for(unsigned int i = 0; i < framesPerBuffer; i++)
    {
        *ob++ = *ib++;
        *ob++ = *ib++;
    }
    return 0;
}

int PortaudioWrapper::MicroToBuffer(const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData)
{
	short *ib = (short *)inputBuffer;
	SoundBuffer *b = (SoundBuffer *)userData;

	for(unsigned int i = 0; i < framesPerBuffer; i++)
    {
		b->buffer[b->max_idx] = *ib++;
		b->max_idx++;
		b->buffer[b->max_idx] = *ib++;
		b->max_idx++;
    }

	return (0);
}

int	PortaudioWrapper::BufferToSpeaker(const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData)
{
	short *ob = (short *)outputBuffer;
	SoundBuffer *b = (SoundBuffer *)userData;
    
	for(unsigned int i = 0; i < framesPerBuffer; i++)
    {
		*ob++ = b->buffer[b->idx];
		b->idx++;
		*ob++ = b->buffer[b->idx];
		b->idx++;
    }
	return (0);
}

#define ENCODING true
#define DECODING false
#define WAIT 3

int PortaudioWrapper::MicroToSpeex(const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData)
{
	SpeexBuffer		*s = (SpeexBuffer *)userData;
	short			*tmp = new short[framesPerBuffer];
	short			*ib = (short *)inputBuffer;



//s->son = new short[framesPerBuffer];

	if (s->state == ENCODING)
	{
		for (unsigned int i = 0; i < framesPerBuffer; i++, ib++)
                {
                    tmp[i] = *ib;
      //              s->son[i] = *ib;
             }
		s->buf = new char[s->encoder->FrameSize() + 1];
		s->size_encoded = s->encoder->Encode(tmp, s->buf);
		delete tmp;
                //ici on send
//                std::string log = "t";
//                Protocol::getInstance()->send(log, Protocol::AUDIO, (void*)(s->buf), s->size_encoded);
   //             s->state = DECODING;

                std::list<std::string> const & loglist = AudioThreadSingleton::getInstance()->getLoginList();
                std::cout << "GROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOS" << loglist.size() << std::endl;
                if (loglist.size() != 0)
                    {
                        for (std::list<std::string>::const_iterator it = loglist.begin(); it != loglist.end(); ++it)
                        {
                            Protocol::getInstance()->send((*it), Protocol::AUDIO, (void *)s->buf, s->size_encoded);
                        }
                    }
                AudioThreadSingleton::getInstance()->freeLoginList();

                //s->state = WAIT;
                //faire le send ici.
        }
	return (0);
}

int PortaudioWrapper::SpeexToSpeaker(const void *inputBuffer,
					void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData)
{
	SpeexBuffer		*s = (SpeexBuffer *)userData;
	short			*tmp;
	short			*ob = (short *)outputBuffer;


        std::cout << framesPerBuffer << std::endl;
        if (s->state == DECODING)
        {
                tmp = s->decoder->Decode(s->buf, s->size_encoded);

		for (unsigned int i = 0; i < framesPerBuffer; i++, ob++)
		{
        //            *ob = s->son[i];
                *ob = tmp[i];
		}

 //              delete s->son;
                delete s->buf;
               s->state = ENCODING;
              // s->state = WAIT;
        }

	return (0);
}
