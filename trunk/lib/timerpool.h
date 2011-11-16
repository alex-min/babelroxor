#ifndef TIMERPOOL_H
#define TIMERPOOL_H
#include <time.h>
#include "portablelibrary.h"
#include "iportablesocket.h"
#include "singleton.h"
#include "protocol.h"
#include "packet.h"

class TimerPool
{
public:
    typedef std::map<Packet *, std::pair<unsigned int, std::pair<ISlotInterface *, Protocol::SlotCall> > > PoolMap;

    TimerPool();
    int getMsNextCall();
    void addToPool(Packet *pack,
                   unsigned int timeout = Protocol::DEFAULT_TIMEOUT);
    void removeFromPool(Packet *);
    void autocall();

    PoolMap _pool;
};

typedef Singleton<TimerPool> TimerPoolSingleton;

#endif // TIMERPOOL_H
