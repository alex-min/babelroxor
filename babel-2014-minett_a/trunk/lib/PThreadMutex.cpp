#include "PThreadMutex.h"

PThreadMutex::PThreadMutex()
{
  if (pthread_mutex_init(&_mut, NULL) > 0)
    throw std::exception();
}

PThreadMutex::~PThreadMutex()
{
  pthread_mutex_destroy(&_mut);
}

void PThreadMutex::lock()
{
  pthread_mutex_lock(&_mut);
}

void PThreadMutex::unlock()
{
  pthread_mutex_unlock(&_mut);
}

bool PThreadMutex::trylock()
{
  if (!(pthread_mutex_trylock(&_mut)))
    return (true);
  return (false);
}

IMutex *PThreadMutex::create()
{
  return (new PThreadMutex);
}

