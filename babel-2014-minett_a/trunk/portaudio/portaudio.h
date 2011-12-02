#ifndef PORTAUDIO_H
#define PORTAUDIO_H

#include <stdio.h>
#include <stdlib.h>
#include "portaudio2.h"

#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_CHANNELS    (2)
#define DITHER_FLAG     (0) /**/


#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"

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
    void    init(int sec = 5);
    void    setInput();
    void    setOutput();
    void    setFrames(SAMPLE *datas);
    SAMPLE  *getFrames();
    unsigned long getFrameSize() const;

    int recordCallback(const void *inputBuffer,
                              void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData);
    int playCallback(const void *inputBuffer,
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
    int                 _numSamples;
    int                 _numBytes;
    SAMPLE              _max, _val;
    double              _average;
    int                 _totalFrameses;
};

#endif // PORTAUDIO_H
