#ifndef _AUDIOCALLBACK_H_
# define _AUDIOCALLBACK_H_

#include "portaudio2.h"
#include "EncoderSpeex.h"
#include "DecoderSpeex.h"

#define ENCODING true
#define DECODING false

using namespace Audio2;

namespace PortaudioWrapper
{
	typedef struct	SpeexBuffer_s
	{
                DecoderSpeex		*decoder;
                EncoderSpeex		*encoder;
                char			*buf;
                int			size_encoded;
                bool			state;
	}				SpeexBuffer;

        int SendEncode(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
									const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
									void *userData);

        int ReceiveDecode(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
									const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
									void *userData);
}

#endif
