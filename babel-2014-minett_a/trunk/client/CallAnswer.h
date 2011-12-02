#ifndef CALLANSWER_H
#define CALLANSWER_H

#include "singleton.h"
#include "islotinterface.h"
#include "DockWidgetContent.h"

class CallAnswer : public ISlotInterface
{
public:
    CallAnswer();
    virtual void    onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header);
    std::string const &getLogin();
    void              resetLogin();

private:
   std::string _login;
};

typedef Singleton<CallAnswer>   CallAnswerSingleton;

#endif // CALLANSWER_H
