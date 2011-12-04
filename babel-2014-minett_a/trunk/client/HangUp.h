#ifndef HANGUP_H
#define HANGUP_H

#include "singleton.h"
#include "protocol.h"

class HangUp
{
public:
    HangUp();
    void sendHangUp(std::string const &senderLogin, std::string const &contactLogin);
};

typedef Singleton<HangUp>   HangUpSingleton;

#endif // HANGUP_H
