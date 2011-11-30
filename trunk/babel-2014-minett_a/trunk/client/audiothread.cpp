#include "audiothread.h"
#include <unistd.h>

AudioThread::AudioThread()
{
}

void AudioThread::run()
{
    Sleep(5);
    _pa.init();
    _pa.setInput();
    while (1)
    {
        _pa.record(1);
        SAMPLE *s = _pa.getFrames();
        Protocol::getInstance()->send("lol", Protocol::AUDIO, s, _pa.getFrameSize());
    }
//  sleep(5);
//  while (1) {
//      Protocol::getInstance()->send("", Protocol::AUDIO, "hello world", 11);
//      ::usleep(50000);
//   }
}
