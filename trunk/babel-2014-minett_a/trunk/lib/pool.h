#ifndef POOL_H
#define POOL_H
#include <map>
#include "singleton.h"

template <class T> class PoolFactory {

public:
    PoolFactory()
    {
        _num_active = 0;
    }

    T *generate()
    {
        if (_num_active == 0)
        {
            T *a = new T();
            _active[a] = false;
            return new T();
        }
        for (typename std::map<T *, bool>::iterator it = _active.begin(); it != _active.end(); ++it)
        {
            if (it->second == true)
            {
                it->first->erase();
                it->second = false;
                _num_active--;
                if (_num_active < 0)
                    _num_active = 0;
                return (it->first);
            }
        }
        T *a = new T();
        _active[a] = false;
        return (a);
    }

    void invalidate(T *a)
    {
        _active[a] = true;
        _num_active++;
    }

protected:
    std::map<T *, bool> _active;
    int _num_active;
};


#define Pool(a) Singleton< PoolFactory < a > >

#endif // POOL_H
