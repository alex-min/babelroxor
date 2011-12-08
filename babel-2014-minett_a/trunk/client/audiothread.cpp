#include "audiothread.h"
#include <unistd.h>

AudioThread::AudioThread()
{
    _m.create();
    _s.encoder = new EncoderSpeex(5);
    _s.decoder = new DecoderSpeex;
    _s.state = true;
    if (_enc.good())
    {
        _enc.setCallback(PortaudioWrapper::MicroToSpeex);
        _enc.setInputDevice(1);
        _enc.openStream(1, 0, &_s, paInt16, _s.encoder->Rate(), _s.encoder->FrameSize());
    }

}

void AudioThread::addLogin(std::string const & login)
{
    _loginCall.push_back(login);
}

void AudioThread::removeLogin(std::string const & login)
{
    _m.lock();
    _loginCall.remove(login);
     _m.unlock();
}

std::list<std::string> & AudioThread::getLoginList()
{
    _m.lock();
    return (_loginCall);
}

void AudioThread::releaseLoginList()
{
    _m.lock();
}

void AudioThread::freeLoginList()
{
    _m.unlock();
}

void AudioThread::run()
{
    std::cout << "Ca passe dans le run" << std::endl;

        if (_enc.good())
        {
           _enc.start();
           //Sleep(10000);
 //          _enc.stop();
        }


//    _pa.init(1);
//    _pa.setInput();
//    while (1)
//    {
//        if (AudioThread::getLoginList().size() != 0)
//        {
//            std::cout << "On a du monde" << std::endl;
//            _pa.record(1);
//            SAMPLE *s = _pa.getFrames();
//            std::cout << "Size:" << (int)_pa.getFrameSize() << std::endl;
//            Protocol::getInstance()->send("lol", Protocol::AUDIO, s, 200, 333, true);
//        }
//        else {
//            usleep(50000);
//        }
//        _m.unlock();
//    }
//  sleep(5);
//  while (1) {
//      Protocol::getInstance()->send("", Protocol::AUDIO, "hello world", 11);
//      ::usleep(50000);
//   }
}
