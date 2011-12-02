#include "portaudio.h"
#include "My_Speex.h"
#include <iostream>

portAudio::portAudio()
{

}

void    portAudio::init(int msec)
{
    _err = paNoError;


    My_Speex::Encode ecodage;

    //_data.maxFrameIndex = _totalFrameses = msec * SAMPLE_RATE;
    _data.maxFrameIndex = ecodage.getFrame_size() / (NUM_CHANNELS * sizeof(SAMPLE));
    _totalFrameses = ecodage.getFrame_size() / (NUM_CHANNELS * sizeof(SAMPLE));
    std::cout << _data.maxFrameIndex << " " << ecodage.getFrame_size() << std::endl;
    _data.frameIndex = 0;
    _numSamples = _totalFrameses * NUM_CHANNELS;
    _numBytes = _numSamples * sizeof(SAMPLE);
    _data.recordedSamples = (SAMPLE *) malloc( _numBytes );
    if( _data.recordedSamples == NULL )
        delAll();

    for( int i=0; i < _numSamples; i++ ) _data.recordedSamples[i] = 0;

    _err = Pa_Initialize();
    if( _err != paNoError )
        delAll();
}

void    portAudio::setInput()
{
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice)
        delAll();
    _inputParameters.channelCount = 2;
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo( _inputParameters.device )->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = NULL;
}

int portAudio::record(bool writeToFile)
{
    _err = Pa_OpenStream(
              &stream,
              &_inputParameters,
              NULL,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,
              recordCallback,
              &_data );
    if( _err != paNoError )
        delAll();
    _err = Pa_StartStream( stream );
    if( _err != paNoError )
        delAll(); //goto done;
    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);

    while( ( _err = Pa_IsStreamActive( stream ) ) == 1 )
    {
        Pa_Sleep(1000);
        printf("index = %d\n", _data.frameIndex ); fflush(stdout);
    }
    if( _err < 0 )
        delAll();

    _err = Pa_CloseStream( stream );
    if( _err != paNoError )
        delAll();

    if (writeToFile)
    {
        FILE  *fid;
        fid = fopen("toto4242.raw", "wb");
        if( fid != NULL )
        {
            fwrite( _data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), _totalFrameses, fid );
            fclose( fid );
            printf("Wrote data to 'recorded.raw'\n");
        }
    }
    return _err;
}

unsigned long portAudio::getFrameSize() const
{
    return (NUM_CHANNELS * sizeof(SAMPLE) * _totalFrameses);
}

SAMPLE  *portAudio::getFrames()
{
    return _data.recordedSamples;
}

void    portAudio::setFrames(SAMPLE *datas)
{
    _data.recordedSamples = datas;
}

int portAudio::recordCallback(const void *inputBuffer,
                          void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    paTestData *data = (paTestData*)userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    //unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
    unsigned long framesLeft = _totalFrameses - data->frameIndex;

    (void) outputBuffer;
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        framesToCalc = framesLeft;
        finished = paComplete;
    }
    else
    {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }

    if( inputBuffer == NULL )
    {
        for( i=0; i<framesToCalc; i++ )
        {
            *wptr++ = SAMPLE_SILENCE;
            if( NUM_CHANNELS == 2 )
                *wptr++ = SAMPLE_SILENCE;
        }
    }
    else
    {
        for( i=0; i<framesToCalc; i++ )
        {
            *wptr++ = *rptr++;
            if( NUM_CHANNELS == 2 )
                *wptr++ = *rptr++;
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

void    portAudio::setOutput()
{
    _data.frameIndex = 0;

    _outputParameters.device = Pa_GetDefaultOutputDevice();
    if (_outputParameters.device == paNoDevice)
        delAll();
    _outputParameters.channelCount = 2;
    _outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo( _outputParameters.device )->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;
}

int portAudio::play()
{
    printf("\n=== Now playing back. ===\n"); fflush(stdout);
    _err = Pa_OpenStream(
              &stream,
              NULL,
              &_outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,
              playCallback,
              &_data );
    if( _err != paNoError )
        delAll();

    if( stream )
    {
        _err = Pa_StartStream( stream );
        if( _err != paNoError )
            delAll();

        printf("Waiting for playback to finish.\n"); fflush(stdout);

        while( ( _err = Pa_IsStreamActive( stream ) ) == 1 )
            Pa_Sleep(100);
        if( _err < 0 )
            delAll();

        _err = Pa_CloseStream( stream );
        if( _err != paNoError )
            delAll();
    }
    return _err;
}

int portAudio::playCallback(const void *inputBuffer,
                        void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData)
{
    paTestData *data = (paTestData*)userData;
    SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    SAMPLE *wptr = (SAMPLE*)outputBuffer;
    unsigned int i;
    int finished;
    //unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;
    unsigned int framesLeft = _totalFrameses - data->frameIndex;

    (void) inputBuffer;
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        for( i=0; i<framesLeft; i++ )
        {
            *wptr++ = *rptr++;
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;
        }
        for( ; i<framesPerBuffer; i++ )
        {
            *wptr++ = 0;
            if( NUM_CHANNELS == 2 ) *wptr++ = 0;
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    }
    else
    {
        for( i=0; i<framesPerBuffer; i++ )
        {
            *wptr++ = *rptr++;
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}

void portAudio::delAll()
{
   Pa_Terminate();
   if( _data.recordedSamples )
       free( _data.recordedSamples );
}

portAudio::~portAudio()
{
    delAll();
}
