#ifndef IMUTEX_H_
#define IMUTEX_H_

#include <iostream>
#include <exception>

class IMutex
{
public :
  virtual ~IMutex(void) {};
  virtual void lock() = 0;
  virtual void unlock() = 0;
  virtual bool trylock() = 0;
  virtual IMutex *create() = 0;
};

class MutexImplement
{
public:
  static IMutex *createMutex();
  static void setImplementation(IMutex *);
  static void destroy();

  static IMutex *_implement;
};

#include "PThreadMutex.h"



#endif
