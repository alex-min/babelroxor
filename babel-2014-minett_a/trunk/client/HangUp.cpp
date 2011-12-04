#include "HangUp.h"

HangUp::HangUp()
{

}

void    HangUp::sendHangUp(std::string const &senderLogin, std::string const &contactLogin)
{
    Protocol::getInstance()->send(contactLogin, Protocol::HANGUP, senderLogin.c_str(), senderLogin.length(), false);
}

