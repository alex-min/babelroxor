#ifndef PTHREADMUTEX_H_
#define PTHREADMUTEX_H_

#include <pthread.h>
#include "IMutex.h"

class PThreadMutex : public IMutex
{
public:
  PThreadMutex();
  virtual ~PThreadMutex();
  virtual void lock();
  virtual void unlock();
  virtual bool trylock();
  virtual IMutex *create();
private:
  pthread_mutex_t _mut;
};

typedef PThreadMutex Mutex;

#endif
