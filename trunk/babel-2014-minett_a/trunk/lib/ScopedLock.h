#ifndef SCOPEDLOCK_H_
#define SCOPEDLOCK_H_

#include "IMutex.h"

class ScopedLock
{
public:
  ScopedLock(IMutex *);
  ~ScopedLock();
private:
  IMutex *_mut;
};


#endif
