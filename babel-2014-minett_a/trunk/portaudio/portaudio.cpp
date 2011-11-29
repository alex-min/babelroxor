#include "portaudio.h"

portAudio::portAudio()
{

}

void    portAudio::init(int sec)
{
    _err = paNoError;

    _data.maxFrameIndex = _totalFrames = sec * SAMPLE_RATE;
    _data.frameIndex = 0;
    _numSamples = _totalFrames * NUM_CHANNELS;
    _numBytes = _numSamples * sizeof(SAMPLE);
    _data.recordedSamples = (SAMPLE *) malloc( _numBytes );
    if( _data.recordedSamples == NULL )
    {
        printf("Could not allocate record array.\n");
        delAll();
    }

    for( int i=0; i < _numSamples; i++ ) _data.recordedSamples[i] = 0;

    _err = Pa_Initialize();
    if( _err != paNoError )
        delAll();
}

void    portAudio::setInput()
{
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice)
    {
        fprintf(stderr,"Error: No default input device.\n");
        delAll();
    }
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
        delAll(); //goto done;

    _err = Pa_CloseStream( stream );
    if( _err != paNoError )
        delAll();

    if (writeToFile)
    {
        FILE  *fid;
        fid = fopen("recorded.raw", "wb");
        if( fid == NULL )
        {
            printf("Could not open file.");
        }
        else
        {
            fwrite( _data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), _totalFrames, fid );
            fclose( fid );
            printf("Wrote data to 'recorded.raw'\n");
        }
    }
    return _err;
}

unsigned long portAudio::getFrameSize() const
{
    return (NUM_CHANNELS * sizeof(SAMPLE) * _totalFrames);
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
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

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
    if (_outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        delAll(); //goto done;
    }
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
              NULL, /* no input */
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

        printf("Done.\n"); fflush(stdout);
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
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    (void) inputBuffer;
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        /* final buffer... */
        for( i=0; i<framesLeft; i++ )
        {
            *wptr++ = *rptr++;
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;
        }
        for( ; i<framesPerBuffer; i++ )
        {
            *wptr++ = 0;  /* left */
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
   if( _err != paNoError )
   {
       fprintf( stderr, "An error occured while using the portaudio stream\n" );
       fprintf( stderr, "Error number: %d\n", _err );
       fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( _err ) );
       _err = 1;
   }
}

portAudio::~portAudio()
{
    delAll();
}
