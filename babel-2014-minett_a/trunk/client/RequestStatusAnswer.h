#ifndef REQUESTSTATUSANSWER_H
#define REQUESTSTATUSANSWER_H

#include "islotinterface.h"
#include "singleton.h"

class RequestStatusAnswer : public ISlotInterface
{
public:
    RequestStatusAnswer();
    virtual void    onCall(Network *network, std::string const & login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);
};

typedef Singleton<RequestStatusAnswer> RequestStatusAnswerSingleton;

#endif // REQUESTSTATUSANSWER_H
