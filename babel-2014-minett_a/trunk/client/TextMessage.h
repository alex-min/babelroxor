#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "singleton.h"
#include "protocol.h"

class TextMessage
{
public:
    TextMessage();
    void    sendTextMessage(std::string const &login, std::string const &text);
    ~TextMessage();
};

typedef Singleton<TextMessage>  TextMessageSingleton;

#endif // TEXTMESSAGE_H
