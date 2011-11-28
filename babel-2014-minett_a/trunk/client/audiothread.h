#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
#include "Thread.h"
#include "protocol.h"

class AudioThread : public Thread
{
public:
    AudioThread();
    virtual void run();
};

#endif // AUDIOTHREAD_H
