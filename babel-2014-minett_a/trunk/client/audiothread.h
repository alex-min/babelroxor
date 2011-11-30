#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
#include "Thread.h"
#include "protocol.h"
#include "portaudio.h"
#include <QThread>
#include <list>
#include "singleton.h"

class AudioThread : public QThread
{
public:
    AudioThread();
    virtual void run();
    void addLogin(std::string const & login);
    std::list<std::string> & getLoginList();

private:
    portAudio _pa;
    std::list<std::string> _loginCall;
    Mutex _m;
};

typedef Singleton<AudioThread> AudioThreadSingleton;

#endif // AUDIOTHREAD_H
