#ifndef AUDIO_DECODER_SPEEX_H_
#define AUDIO_DECODER_SPEEX_H_

#ifndef M_PI
# define M_PI 3.14
#endif

#include <Utils.h>
#include <speex.h>

#include <map>
typedef std::map< unsigned short int, SpeexBits > SpeexBitsUserMap;

namespace Audio2
{
  class DecoderSpeex : Utils::NonCopyable
  {
  public:
    DecoderSpeex();
    ~DecoderSpeex();

	short *Decode(char *bitsToDecode, unsigned int size);


    inline int	FrameSize()	{return _frameSize;}
    inline int	Rate()		{return _rate;}
    static SpeexBits getUserSpeexBits(unsigned short int userId);
  private:
    void	*_state;	// instance of speex decoder
    SpeexBits	_bits;		// structure for decode speex bits
    int		_frameSize;
    int		_rate;
    short	*_decodeResult; // tab where the decode result is stored
	static SpeexBitsUserMap	mSpeexBitsUserMap;
  };
}

#endif
