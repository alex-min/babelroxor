#ifndef MY_SPEEX_H
#define MY_SPEEX_H

#include <speex.h>
#include <QVector>
#include <QByteArray>
#include <speex_bits.h>
#include <speex_buffer.h>
#include <speex_callbacks.h>
#include <speex_echo.h>
#include <speex_header.h>
#include <speex_jitter.h>
#include <speex_preprocess.h>
#include <speex_resampler.h>
#include <speex_stereo.h>
#include <speex_types.h>

namespace My_Speex
{
    class Encode
        {
            public:
                Encode();
                ~Encode();
                int encode(short *b, char *);
                SpeexBits       getBits_enc();
                int             getRate();
                int             getFrame_size();
            private:
                SpeexBits bits_enc;
                int rate;
                int nbBytes;
                void *enc_state;
                int quality;
                int frame_size;
        };
    class Decode
        {
            public:
                 Decode();
                 ~Decode();
                short * decode(char *decode);
                SpeexBits       getBits_dec();
                int             getRate();
                int             getFrame_size();
                short           *getOut();
            private:
                SpeexBits bits_dec;
                int rate;
                void *dec_state;
                short *out;
                int frame_size;
                int nbBytes;
        };
}

#endif // MYSPEEX_H
