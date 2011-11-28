#ifndef PTHREADTHREAD_H_
#define PTHREADTHREAD_H_

#ifdef OS_WINDOWS
#include <pthread.h>
#endif

#include <iostream>
#include "IThread.h"

class PThreadThread : public IThread
{
public:
  virtual ~PThreadThread();
  virtual bool start();
  virtual void kill();
  virtual bool join();

private:
  virtual void die();

private:
  pthread_t _thread;
};

typedef PThreadThread Thread;


void *run_call(void *_this);

#endif
