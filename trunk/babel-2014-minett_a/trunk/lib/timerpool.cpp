#include "timerpool.h"
#include <cstdio>

TimerPool::TimerPool()
{
}

void TimerPool::addToPool(Packet *pack,
               unsigned int timeout)
{
    if (!pack)
        return ;
    PortableTime time;

    time.setToMsTimeOfDay();
    std::cout << "TimerPool::addTotimeout| " << timeout << std::endl;
    _pool[pack].first = time.getMs() + timeout;
    _pool[pack].second = std::pair<ISlotInterface *, Protocol::SlotCall> (pack->getSlot(), pack->getSlotCall());
}

void TimerPool::removeFromPool(Packet *pack)
{
    PoolMap::iterator it;

    if (!pack)
        return ;
    it = _pool.find(pack);
    if (it == _pool.end())
        return ;
    _pool.erase(it);
}

void TimerPool::autocall()
{
    _time.setToMsTimeOfDay();

    PoolMap::iterator it = _pool.begin();
    PoolMap::iterator it2;
    while (it != _pool.end())
    {
       // std::cout << _time.getMs() << " => " << it->second.first << std::endl;
        if (_time.getMs() > it->second.first)
        {
            if (it->second.second.first && it->second.second.second)
              (it->second.second.first->*it->second.second.second)(true, it->first);
            it2 = it;
            if (it->first)
              Protocol::getInstance()->unregisterPacket(it->first->getId(), it->first->getLogin());
            ++it;


            _pool.erase(it2);
        }
        else
        ++it;
    }

}

int TimerPool::getMsNextCall()
{
    long long time = -1;

    _time.setToMsTimeOfDay();

    for (PoolMap::iterator it = _pool.begin(); it != _pool.end(); ++it)
    {
        if (it->second.first < static_cast<unsigned int>(time) || time < 0)
            time =it->second.first;
    }
    if (time == -1)
        return (TimerPool::DEFAULT_TIMEOUT);
    if (_time.getMs() > static_cast<unsigned long long>(time))
    {
        TimerPool::autocall();
        return (TimerPool::getMsNextCall());
    }
    if (static_cast<unsigned int>(time) - _time.getMs() == 0)
        return (TimerPool::DEFAULT_TIMEOUT);
    if (static_cast<unsigned int>(time) - _time.getMs() > TimerPool::DEFAULT_TIMEOUT)
    return (TimerPool::DEFAULT_TIMEOUT);
    return (static_cast<unsigned int>(time) - _time.getMs());
}
