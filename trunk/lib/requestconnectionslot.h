#ifndef REQUESTCONNECTIONSLOT_H
#define REQUESTCONNECTIONSLOT_H
#include "singleton.h"
#include "islotinterface.h"

class RequestConnectionSlot : public ISlotInterface
{
public:
    virtual void    onCall(Network *network, std::string const &login, void *data, unsigned int len);
};

typedef Singleton<RequestConnectionSlot> RequestConnectionSlotSingleton;

#endif // REQUESTCONNECTIONSLOT_H
