#ifndef REGISTERACCOUNT_H
#define REGISTERACCOUNT_H

#include "islotinterface.h"
#include "singleton.h"

class RegisterAccount : public ISlotInterface
{
public:
    RegisterAccount();
    void onCall(Network *network, const std::string &login, void *data, unsigned int len, Protocol::NetworkPacket::NetworkHeader *header);
};

typedef Singleton<RegisterAccount>  RegisterAccountSingleton;

#endif // REGISTERACCOUNT_H
