#ifndef _AUDIOCALLBACK_H_
# define _AUDIOCALLBACK_H_

#include "portaudio2.h"
#include "EncoderSpeex.h"
#include "DecoderSpeex.h"

using namespace Audio2;

namespace PortaudioWrapper
{
	typedef struct	SoundBuffer_s
	{
		short *buffer;
		unsigned int idx;
		unsigned int max_idx;
	}				SoundBuffer;

	typedef struct	SpeexBuffer_s
	{
                DecoderSpeex		*decoder;
                EncoderSpeex		*encoder;
                char			*buf;
                int			size_encoded;
                bool			state;
	}				SpeexBuffer;

	int	MicroToSpeaker(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
						void *userData);


	int MicroToBuffer(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
						void *userData);

	int	BufferToSpeaker(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
						void *userData);

	int MicroToSpeex(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
									const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
									void *userData);

	int SpeexToSpeaker(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
									const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
									void *userData);
}

#endif
