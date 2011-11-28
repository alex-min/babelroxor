#include "PThreadThread.h"

PThreadThread::~PThreadThread(void)
{

}

void *run_call(void *_this)
{
  PThreadThread *call = reinterpret_cast<PThreadThread *>(_this);
  call->run();
  return (_this);
}

bool PThreadThread::start()
{
  if (pthread_create(&_thread,
		 NULL,
		 &run_call,
		     this) != 0)
    return (false);
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  return (true);
}

void PThreadThread::die()
{
  pthread_exit(NULL);
}

void PThreadThread::kill()
{
  pthread_cancel(_thread);
}


bool PThreadThread::join()
{
  void *uval;

  if (pthread_join(_thread, &uval) != 0)
    return (false);
  return (true);
}
