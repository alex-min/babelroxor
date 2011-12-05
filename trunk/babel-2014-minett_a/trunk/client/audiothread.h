#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H
#include "Thread.h"
#include "protocol.h"
#include "portaudio.h"
#include <QThread>
#include <list>
#include "singleton.h"

#include "AudioCallback.h"
#include "AudioHandler.h"
#include "DecoderSpeex.h"
#include "EncoderSpeex.h"


class AudioThread : public QThread
{
public:
    AudioThread();
    virtual void run();
    void addLogin(std::string const & login);
    std::list<std::string> & getLoginList();

    void        releaseLoginList();
    void        freeLoginList();
private:
    PortaudioWrapper::SpeexBuffer	_s;
   PortaudioWrapper::AudioHandler	_enc;
    std::list<std::string> _loginCall;
    Mutex _m;
};

typedef Singleton<AudioThread> AudioThreadSingleton;

#endif // AUDIOTHREAD_H
