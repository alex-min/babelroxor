#include "audiothread.h"
#include <unistd.h>

AudioThread::AudioThread()
{
    _m.create();
}

void AudioThread::addLogin(std::string const & login)
{
    _loginCall.push_back(login);
}

std::list<std::string> & AudioThread::getLoginList()
{
    _m.lock();
    return (_loginCall);
}

void AudioThread::run()
{
    _m.unlock();

//   //Ici on encode et on balance ur le reseaux.
//    std::cout << "on test si ya du monde" << std::endl;
//    if (!_loginCall.empty())
//    {
//        std::cout << "ya du monde !" << std::endl;
//        _s.encoder = new EncoderSpeex(5);
//        _s.decoder = new DecoderSpeex;
//        _s.state = true;
//        if (_enc.good())
//        {
//            _enc.setCallback(PortaudioWrapper::MicroToSpeex);
//            _enc.setInputDevice(1);
//            _enc.openStream(1, 0, &_s, paInt16, _s.encoder->Rate(), _s.encoder->FrameSize());
//            if (_enc.good())
//            {
//              _enc.start();
//              _enc.stop();
//            }
//        }
//    }
//    Sleep(500);
}
