#include "DecoderSpeex.h"


using namespace Audio2;

DecoderSpeex::DecoderSpeex()
{
  _rate = 8000; // sampling rate at 8kHz
  _frameSize = 0;

//   speex_bits_init(&_bits);  // init the structure bits
  speex_bits_init(&_bits);

  // create a new decoder state in narrowband mode
  _state = speex_decoder_init(speex_lib_get_mode(SPEEX_MODEID_WB));
  if (!_state)
    throw Utils::Exception("DecoderSpeex", "initialization failed.");

  // set and get proprieties
  //int tmp = 1;
  //speex_decoder_ctl(_state, SPEEX_SET_ENH, &tmp);
  speex_decoder_ctl(_state, SPEEX_GET_FRAME_SIZE, &_frameSize);
  _decodeResult = new short[_frameSize + 1];
  speex_decoder_ctl(_state, SPEEX_SET_SAMPLING_RATE, &_rate);

}

DecoderSpeex::~DecoderSpeex()
{
  delete _decodeResult;
  speex_decoder_destroy(_state);
  speex_bits_destroy(&_bits);
}

short *DecoderSpeex::Decode(char *bitsToDecode, unsigned int)
{
  int ret;

  memset(_decodeResult, 0, _frameSize);
  speex_bits_read_from(&_bits, bitsToDecode, (int)strlen(bitsToDecode)/*size*/);
  ret = speex_decode_int(_state, &_bits, _decodeResult);
  if (ret == -2)
    throw Utils::Exception("Decoding error", "corrupted stream");
//  else if (speex_bits_remaining(&_bits) < 0)
//    throw Utils::Exception("Decoding overflow", "corrupted stream");

  return _decodeResult;
}
