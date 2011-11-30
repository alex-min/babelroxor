#include "audiothread.h"
#include <unistd.h>

AudioThread::AudioThread()
{
}

void AudioThread::addLogin(std::string const & login)
{
    ScopedLock s(&_m);
    _loginCall.push_back(login);
}

std::list<std::string> & AudioThread::getLoginList()
{
    _m.lock();
    return (_loginCall);
}

void AudioThread::run()
{
    while (1) { ::usleep(50000); }
    _pa.init(1);
    _pa.setInput();
    while (1)
    {
        if (AudioThread::getLoginList().size() != 0)
        {
            std::cout << "On a du monde" << std::endl;
            _pa.record();
            SAMPLE *s = _pa.getFrames();
            Protocol::getInstance()->send("lol", Protocol::AUDIO, s, 200, 333, true);
        }
        else {
            usleep(50000);
        }
        _m.unlock();
    }
//  sleep(5);
//  while (1) {
//      Protocol::getInstance()->send("", Protocol::AUDIO, "hello world", 11);
//      ::usleep(50000);
//   }
}
