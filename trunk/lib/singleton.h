#ifndef SINGLETON_H
#define SINGLETON_H

template <class T> class Singleton  {
protected:
    Singleton();
public:
    static T *getInstance() {
        if (!_instance)
            _instance = new T();
        return (_instance);
    }

    static T *_instance;
};

template <class T>
T *Singleton<T>::_instance = 0;


#endif // SINGLETON_H
