#ifndef HANGUPANSWER_H
#define HANGUPANSWER_H

#include "islotinterface.h"
#include "singleton.h"

class HangUpAnswer : public ISlotInterface
{
public:
    HangUpAnswer();
    virtual void    onCall(Network *network, std::string const & login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);
};

typedef Singleton<HangUpAnswer> HangUpAnswerSingleton;

#endif // HANGUPANSWER_H
