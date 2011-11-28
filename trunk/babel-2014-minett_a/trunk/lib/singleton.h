#ifndef SINGLETON_H
#define SINGLETON_H

#include "mutex.h"
#include "ScopedLock.h"

template <class T> class Singleton  {
protected:
    Singleton();
public:
    static T *getInstance()
    {
        //ScopedLock  scopedLock(&_createInstanceMut);
        if (!_instance)
        {
            _createInstanceMut.lock();
            if (!_instance)
            {
              _instance = new T();
            }
            _createInstanceMut.unlock();
            return (_instance);
        }
    }

    static void deleteInstance()
    {
      //  ScopedLock  scopedLock(&_deleteInstanceMut);

        if (_instance)
            delete _instance;
        _instance = 0;
    }
    static T *_instance;

private:
    static Mutex   _createInstanceMut;
    //static Mutex   _deleteInstanceMut;
};

template <class T>
T *Singleton<T>::_instance = 0;

template <class T>
Mutex Singleton<T>::_createInstanceMut;

#endif // SINGLETON_H
