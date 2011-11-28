#ifndef MY_SPEEX_H
#define MY_SPEEX_H

#include <speex/speex.h>
#include <QVector>
#include <QByteArray>
#include <speex/speex_bits.h>
#include <speex/speex_buffer.h>
#include <speex/speex_callbacks.h>
#include <speex/speex_echo.h>
#include <speex/speex_header.h>
#include <speex/speex_jitter.h>
#include <speex/speex_preprocess.h>
#include <speex/speex_resampler.h>
#include <speex/speex_stereo.h>
#include <speex/speex_types.h>

 #define FRAME_SIZE 160


/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/
/** Set to 1 if you want to capture the recording to a file. */
#define WRITE_TO_FILE   (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
    int          frameIndex;  /* Index into sample array. */
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}
paTestData;

namespace My_Speex
{
    class Encode
        {
            public:
             Encode();
             ~Encode();
            char * encode(short *b);

            SpeexBits ebits;
            /*Holds bits so they can be read and written to by the Speex routines*/
            SpeexBits bits_enc;
            float input[FRAME_SIZE];
            char cbits[200];
            int nbBytes;
            /*Holds the state of the encoder*/
            void *enc_state;
            int quality;
        };
    class Decode
        {
            public:
             Decode();
             ~Decode();
            SAMPLE * decode(char *decode, int size);

            SpeexBits bits_dec;
            void *dec_state;
            /*Holds the audio that will be written to file (16 bits per sample)*/
            short out[FRAME_SIZE];
            /*Speex handle samples as float, so we need an array of floats*/
            float output[FRAME_SIZE];
            char cbits[200];
            int nbBytes;
            /*Holds the state of the decoder*/
            SpeexBits bits;
            int tmp;
        };
}

#endif // MYSPEEX_H
