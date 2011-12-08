#include "EncoderSpeex.h"

using namespace Audio2;

EncoderSpeex::EncoderSpeex(int quality)
{
  _rate = 8000;
  _frameSize = 0;

  //Create a new encoder state in narrowband mode
  _state = speex_encoder_init(speex_lib_get_mode(SPEEX_MODEID_WB));
  speex_encoder_ctl(_state, SPEEX_SET_QUALITY, &quality);
  speex_encoder_ctl(_state, SPEEX_GET_FRAME_SIZE, &_frameSize);
  speex_encoder_ctl(_state, SPEEX_SET_SAMPLING_RATE, &_rate);
 
  _preProcessorState = speex_preprocess_state_init(_frameSize, _rate);

  int	active = 1;
  speex_preprocess_ctl(_preProcessorState, SPEEX_PREPROCESS_SET_VAD, &active);
  speex_preprocess_ctl(_preProcessorState, SPEEX_PREPROCESS_SET_DENOISE, &active);
  speex_preprocess_ctl(_preProcessorState, SPEEX_PREPROCESS_SET_DEREVERB, &active);
  speex_preprocess_ctl(_preProcessorState, SPEEX_PREPROCESS_SET_AGC, &active);

  speex_encoder_ctl(_state, SPEEX_SET_VAD, &active);

  speex_bits_init(&_bits);
}

EncoderSpeex::~EncoderSpeex()
{
  speex_encoder_destroy(_state);
  speex_preprocess_state_destroy(_preProcessorState);
  speex_bits_destroy(&_bits);
}

unsigned int	EncoderSpeex::Encode(short *input, char *output)
{
	unsigned int	nbBytes = 0;
	int				isSpeaking = 0;

	speex_bits_reset(&_bits);
	if ((isSpeaking = speex_preprocess(_preProcessorState, input, 0)) == 0)
		return 0;
	speex_encode_int(_state, input, &_bits);
	nbBytes = speex_bits_nbytes(&_bits);
	speex_bits_write(&_bits, output, _frameSize);
	output[_frameSize] = 0;
     //   std::cout << "nBytes" << nbBytes << std::endl;
	return nbBytes;
}
