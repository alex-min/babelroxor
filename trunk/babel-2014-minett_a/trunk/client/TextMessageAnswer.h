#ifndef TEXTMESSAGEANSWER_H
#define TEXTMESSAGEANSWER_H

#include "islotinterface.h"
#include "singleton.h"

class TextMessageAnswer : public ISlotInterface
{
public:
    TextMessageAnswer();
    virtual void    onCall(Network *network, std::string const & login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);
};

typedef Singleton<TextMessageAnswer> TextMessageAnswerSingleton;

#endif // TEXTMESSAGEANSWER_H
