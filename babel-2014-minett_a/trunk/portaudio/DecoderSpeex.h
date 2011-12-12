#ifndef AUDIO_DECODER_SPEEX_H_
#define AUDIO_DECODER_SPEEX_H_

#include "Utils.h"
#include <speex.h>
#include <ISpeexDecode.h>

namespace Audio2
{
  class DecoderSpeex : public ISpeexdecode
  {
  public:
    DecoderSpeex();
    ~DecoderSpeex();

    short *Decode(char *bitsToDecode, unsigned int size);


    inline int	FrameSize()	{return _frameSize;}
    inline int	Rate()		{return _rate;}
    static SpeexBits getUserSpeexBits(unsigned short int userId);
  private:
    void	*_state;
    SpeexBits	_bits;
    int		_frameSize;
    int		_rate;
    short	*_decodeResult;
  };
}

#endif
