#ifndef ITHREAD_H_
#define ITHREAD_H_

#include "IMutex.h"

class IThread
{
public:
  virtual ~IThread() {};
  virtual void run(void) = 0;
  virtual bool start() = 0;
  virtual void kill() = 0;
  virtual bool join() = 0;
private:
  virtual void die() = 0;
};


#endif
