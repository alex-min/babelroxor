#ifndef PORTAUDIO_H
#define PORTAUDIO_H

#include <stdio.h>
#include <stdlib.h>
#include "portaudio2.h"

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
//#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/
/** Set to 1 if you want to capture the recording to a file. */
//#define WRITE_TO_FILE   (1)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 1
/*#define PA_SAMPLE_TYPE  paFloat32
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1*/
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

class portAudio
{
public:
    portAudio();
    ~portAudio();

    int     play();
    int     record(bool writeToFile = false);
    void    delAll();
    void    init(int sec = 500);
    void    setInput();
    void    setOutput();
    void    setFrames(SAMPLE *datas);
    SAMPLE  *getFrames();
    unsigned long getFrameSize() const;

private:
    static int recordCallback(const void *inputBuffer,
                              void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData);
    static int playCallback(const void *inputBuffer,
                            void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);

private:
    PaStream*           stream;
    PaStreamParameters  _inputParameters,
                        _outputParameters;
    PaError             _err;
    paTestData          _data;
    int                 _totalFrames;
    int                 _numSamples;
    int                 _numBytes;
    SAMPLE              _max, _val;
    double              _average;
};

#endif // PORTAUDIO_H
