#include "timerpool.h"

TimerPool::TimerPool()
{
}

void TimerPool::addToPool(Packet *pack,
               unsigned int timeout)
{
    if (!pack)
        return ;
    unsigned int t = ::time(NULL);
    _pool[pack].first = t + timeout;
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
    unsigned int t = time(NULL);
    PoolMap::iterator it = _pool.begin();
    PoolMap::iterator it2;
    while (it != _pool.end())
    {
        if (t < it->second.first)
        {
            if (it->second.second.first)
              (it->second.second.first->*it->second.second.second)(true, it->first);
            it2 = it;
            ++it;
            _pool.erase(it2);
        }
        else
        ++it;
    }

}

int TimerPool::getMsNextCall()
{
    int time = -1;
    unsigned int t = ::time(NULL);
    for (PoolMap::iterator it = _pool.begin(); it != _pool.end(); ++it)
    {
        if (it->second.first < static_cast<unsigned int>(time) || time < 0)
            time = it->second.first;
    }
    if (time == -1)
        return (-1);
    if (t < static_cast<unsigned int>(time))
        return (0);
    return (t - time);
}
