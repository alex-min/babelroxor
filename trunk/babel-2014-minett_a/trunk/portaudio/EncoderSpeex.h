#ifndef AUDIO_ENCODER_SPEEX_H_
#define AUDIO_ENCODER_SPEEX_H_

#ifndef M_PI
# define M_PI 3.14
#endif

#include "Utils.h"
#include <speex.h>
#include <speex_preprocess.h>

namespace Audio2
{
  class EncoderSpeex : public Utils::NonCopyable
  {
  public:
    EncoderSpeex(int quality);
    ~EncoderSpeex();

    unsigned int	Encode(short *input, char *output);

    inline int		FrameSize()	{return _frameSize;}
    inline int		Rate()		{return _rate;}
    char					*_encodeResult;
  private:
    void					*_state;
	SpeexPreprocessState	*_preProcessorState;
    SpeexBits				_bits;
    int						_frameSize;
    int						_rate;

  };
}

#endif
