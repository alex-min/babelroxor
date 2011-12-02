
#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include "Config.h"

namespace Utils
{
    template <typename T>
    class /*LINK_OPTION_UTILS*/  Singleton
    {
        public:
          static T &Instance()
          {
            if (_instance == NULL)
                _instance = new T();
            return *_instance;
            }

          static void DeleteInstance()  {delete _instance;}

          static bool Exist()           {return (_instance != NULL);}

        protected:
            Singleton()                 {_instance = NULL;}
            virtual ~Singleton()        {_instance = NULL;}

            static T   *_instance;
    };

    template <typename T>
    T *Singleton<T>::_instance = NULL;
}

#endif
