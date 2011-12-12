#include "AudioHandler.h"

using namespace PortaudioWrapper;

std::map<PaDeviceIndex, const PaDeviceInfo *>	AudioHandler::_deviceMap;

AudioHandler::AudioHandler()
{
    _err = 0;
    _initialized = false;
    _stream = 0;
    _callback = 0;
    _running = false;
    _inDev = -1;
    _outDev = -1;
    this->_init();
}

AudioHandler::~AudioHandler()
{
    this->_terminate();
}

void	AudioHandler::_terminate()
{
    if (this->_initialized)
    {
        if (this->_stream)
            this->close();
        this->_err = Pa_Terminate();
        if(this->_err != paNoError)
            this->_initialized = false;
    }
}

void	AudioHandler::_init()
{
    if (!this->_initialized)
    {
        this->_err = Pa_Initialize();
        if (this->_err == paNoError)
            this->_initialized = true;
        if (AudioHandler::_deviceMap.empty())
            AudioHandler::updateDeviceMap();
    }
}

void	AudioHandler::updateDeviceMap()
{
    int					numDevices;

    if (!AudioHandler::_deviceMap.empty())
        AudioHandler::_deviceMap.clear();
    numDevices = Pa_GetDeviceCount();
    if (numDevices > 0)
        for(int i = 0; i < numDevices; i++)
            AudioHandler::_deviceMap[i] = Pa_GetDeviceInfo(i);
}

void	AudioHandler::restart()
{
    this->_terminate();
    this->_init();
}

bool	AudioHandler::err()
{
    if (this->_err == paNoError)
        return (false);
    return (true);
}

bool	AudioHandler::good()
{
    return (!this->err());
}

const std::string	AudioHandler::getErrorMsg() const
{
    if (this->_err != paNoError)
        return (Pa_GetErrorText(this->_err));
    return ("Success");
}

void				AudioHandler::setCallback(AudioHandler::CallbackPtr f)
{
    this->_callback = f;
}

AudioHandler		*AudioHandler::setInputDevice(int inputDevice)
{
    this->_inDev = inputDevice;
    return (this);
}

AudioHandler		*AudioHandler::setOutputDevice(int outputDevice)
{
    this->_outDev = outputDevice;
    return (this);
}

const std::map<PaDeviceIndex, const PaDeviceInfo *>	&AudioHandler::getDeviceMap()
{
    if (AudioHandler::_deviceMap.empty())
        AudioHandler::updateDeviceMap();
    return (AudioHandler::_deviceMap);
}

const PaDeviceInfo	*AudioHandler::getDeviceInfo(PaDeviceIndex idx)
{
    if (AudioHandler::_deviceMap.find(idx) != AudioHandler::_deviceMap.end())
        return (AudioHandler::_deviceMap[idx]);
    return (0);
}

void				AudioHandler::start()
{
    if (this->_stream && !this->_running)
    {
        this->_err = Pa_StartStream(this->_stream);
        if (!this->err())
            this->_running = true;
    }
}

void				AudioHandler::stop()
{
    if (this->_stream && this->_running)
    {
        this->_err = Pa_StopStream(this->_stream);
        if (!this->err())
            this->_running = false;
    }
}

void				AudioHandler::close()
{
    if (this->_initialized && this->_stream)
    {
        this->_err = Pa_CloseStream(this->_stream);
        if (!this->err())
        {
            this->_stream = 0;
            this->_running = false;
        }
    }
}

void				AudioHandler::openStream(int nbInputChannel, int nbOutputChannel, void *data, PaSampleFormat sample, int sampleRate, int frameBuffer)
{
    if (!this->_stream && this->_callback)
    {
        if (nbInputChannel > 0)
        {
            this->_inDev = (this->_inDev == -1) ? Pa_GetDefaultInputDevice() : this->_inDev;
            this->_in.device = this->_inDev;
            this->_in.channelCount = (nbInputChannel <= AudioHandler::_deviceMap[this->_inDev]->maxInputChannels
                                      ) ? nbInputChannel : AudioHandler::_deviceMap[this->_inDev]->maxInputChannels;
            this->_in.sampleFormat = sample;
            this->_in.suggestedLatency = Pa_GetDeviceInfo(this->_in.device )->defaultLowInputLatency ;
            this->_in.hostApiSpecificStreamInfo = NULL;
        }

        if (nbOutputChannel > 0)
        {
            this->_outDev = (this->_outDev == -1) ? Pa_GetDefaultOutputDevice() : this->_outDev;
            this->_out.device = this->_outDev;
            this->_out.channelCount = (nbOutputChannel <= AudioHandler::_deviceMap[this->_outDev]->maxOutputChannels
                                       ) ? nbOutputChannel : AudioHandler::_deviceMap[this->_outDev]->maxOutputChannels;
            this->_out.sampleFormat = sample;
            this->_out.suggestedLatency = Pa_GetDeviceInfo(this->_out.device )->defaultLowOutputLatency;
            this->_out.hostApiSpecificStreamInfo = NULL;
        }
        // std::cout << << std::endl;
        this->_err = Pa_OpenStream(
                    &(this->_stream),
                    (nbInputChannel > 0) ? &(this->_in) : 0,
                    (nbOutputChannel > 0) ? &(this->_out) : 0,
                    sampleRate,
                    frameBuffer,
                    paNoFlag,
                    this->_callback,
                    (void *)data);
    }
}

const PaDeviceInfo	*AudioHandler::getCurrentInputDeviceInfo()
{
    if (this->_inDev > 0)
        return (AudioHandler::_deviceMap[this->_inDev]);
    return (0);
}

const PaDeviceInfo	*AudioHandler::getCurrentOutputDeviceInfo()
{
    if (this->_outDev > 0)
        return (AudioHandler::_deviceMap[this->_outDev]);
    return (0);
}
