#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
#include "Thread.h"
#include "protocol.h"
#include "portaudio.h"
#include <QThread>

class AudioThread// : public QThread
{
public:
    AudioThread();
    virtual void run();
private:
    //portAudio _pa;
};

#endif // AUDIOTHREAD_H
