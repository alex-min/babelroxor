#ifndef TIMERPOOL_H
#define TIMERPOOL_H
#include <time.h>
#include "portablelibrary.h"
#include "iportablesocket.h"
#include "singleton.h"
#include "protocol.h"
#include "packet.h"
#include "time.h"

class TimerPool
{
public:
    typedef std::map<Packet *, std::pair<unsigned long long, std::pair<ISlotInterface *, Protocol::SlotCall> > > PoolMap;
    enum {DEFAULT_TIMEOUT = 50};

    TimerPool();
    int getMsNextCall();
    void addToPool(Packet *pack,
                   unsigned int timeout = Protocol::DEFAULT_TIMEOUT);
    void removeFromPool(Packet *);
    void autocall();

    PoolMap _pool;
    PortableTime _time;
};

typedef Singleton<TimerPool> TimerPoolSingleton;

#endif // TIMERPOOL_H
