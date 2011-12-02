#ifndef _AUDIOHANDLER_H_
# define _AUDIOHANDLER_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include "portaudio2.h"

namespace PortaudioWrapper
{
	class	AudioHandler
	{
	public:

		typedef int (*CallbackPtr)(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

		AudioHandler();
		~AudioHandler();

		void				restart();

		bool				err();

		const std::string	getErrorMsg() const;

		bool				good();

		void				setCallback(AudioHandler::CallbackPtr f);

		AudioHandler		*setInputDevice(int inputDevice);

		AudioHandler		*setOutputDevice(int outputDevice);

		const PaDeviceInfo	*getCurrentInputDeviceInfo();
		const PaDeviceInfo	*getCurrentOutputDeviceInfo();

                void				openStream(int nbInputChannel, int nbOutputChannel, void *data = 0, PaSampleFormat sample = paInt16, int sampleRate = 44100, int frameBuffer = paFramesPerBufferUnspecified);

		void				start();

		void				stop();

		void				isActive();

		void				close();

		static const std::map<PaDeviceIndex, const PaDeviceInfo *>	&getDeviceMap();

		static const PaDeviceInfo									*getDeviceInfo(PaDeviceIndex idx);

		static void													updateDeviceMap();

	private:

		void				_init();

		void				_terminate();

		bool				_initialized;
		bool				_running;
                int				_err;
                int				_inDev;
                int				_outDev;
		CallbackPtr			_callback;
		PaStream			*_stream;
		PaStreamParameters	_in;
		PaStreamParameters	_out;
		static std::map<PaDeviceIndex, const PaDeviceInfo *>	_deviceMap;
	};
}
#endif
