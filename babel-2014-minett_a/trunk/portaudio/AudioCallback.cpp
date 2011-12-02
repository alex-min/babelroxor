#include "AudioHandler.h"
#include "AudioCallback.h"


using namespace Audio2;
using namespace PortaudioWrapper;

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


	if (s->state == ENCODING)
	{
		for (unsigned int i = 0; i < framesPerBuffer; i++, ib++)
                    tmp[i] = *ib;
		s->buf = new char[s->encoder->FrameSize() + 1];
		s->size_encoded = s->encoder->Encode(tmp, s->buf);
		delete tmp;
		s->state = DECODING;
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

	if (s->state == DECODING)
	{
		tmp = s->decoder->Decode(s->buf, s->size_encoded);
		for (unsigned int i = 0; i < framesPerBuffer; i++, ob++)
		{
			*ob = tmp[i];
		}
		delete s->buf;
		s->state = ENCODING;
	}
	return (0);
}
