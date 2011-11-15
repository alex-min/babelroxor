#ifndef TIMERPOOL_H
#define TIMERPOOL_H
#include "portablelibrary.h"
#include "iportablesocket.h"
#include "singleton.h"
#include "protocol.h"

class TimerPool
{
public:
    TimerPool();
    unsigned int getMsNextCall();
    void addToPool(ISlotInterface *obj, Protocol::SlotCall call);
};

typedef Singleton<TimerPool> TimerPoolSingleton;

#endif // TIMERPOOL_H
