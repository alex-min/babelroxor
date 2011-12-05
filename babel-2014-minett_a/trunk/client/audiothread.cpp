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

void        AudioThread::releaseLoginList()
{
    _m.lock();
}

void        AudioThread::freeLoginList()
{
    _m.unlock();
}

void AudioThread::run()
{


    PortaudioWrapper::AudioHandler enc;
    PortaudioWrapper::SpeexBuffer	s;


            s.decoder = new DecoderSpeex;
            s.encoder = new EncoderSpeex(5);
            s.state = true;
            if (enc.good())
            {
                    enc.setCallback(PortaudioWrapper::MicroToSpeex);
                    enc.setInputDevice(1);
                    enc.openStream(1, 0, &s, paInt16, s.encoder->Rate(), s.encoder->FrameSize());



                    if (enc.good())
                    {

                            enc.start();

                                Sleep(10000);

                     }

            }



//    while (1)
//    {
//           _m.unlock();
//        if ((loglist = getLoginList().size) != 0)
//        {
//            for (std::iterator<std::string> it, it = loglist.begin(); it != loglist.end(); ++it)
//            {
//                Protocol::send((*it), AUDIO, s, sizeof(PortaudioWrapper));
//            }
//        }
//         _m.lock();
//    }

//    std::cout << "Ca passe dans le run" << std::endl;

//    _s.encoder = new EncoderSpeex(5);
//    _s.decoder = new DecoderSpeex;
//    _s.state = true;
//    if (_enc.good())

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


//     }
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
//    }
//    Sleep(500);
}

