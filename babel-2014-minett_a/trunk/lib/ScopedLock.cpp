#include "ScopedLock.h"

ScopedLock::ScopedLock(IMutex *mut) :
  _mut(mut)
{
  _mut->lock();
}

ScopedLock::~ScopedLock()
{
  _mut->unlock();
}
