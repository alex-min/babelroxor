#ifndef STATUSANSWER_H
#define STATUSANSWER_H

#include "islotinterface.h"
#include "DockWidgetContent.h"
#include "singleton.h"

class StatusAnswer : public ISlotInterface
{
public:
    StatusAnswer();
    virtual void    onCall(Network *network, std::string const & login, void *data, unsigned int len,
                           Protocol::NetworkPacket::NetworkHeader *header);
};

typedef Singleton<StatusAnswer> StatusAnswerSingleton;

#endif // STATUSANSWER_H
