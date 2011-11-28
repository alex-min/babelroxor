#include "circularbuffer.h"

CircularBuffer::CircularBuffer(unsigned int size)
{
    _buf = new char[size];
    _len = size;
    _readPtr = 0;
    _writePtr = 0;
}

CircularBuffer::~CircularBuffer()
{
    delete[] _buf;
}

unsigned int CircularBuffer::getReadSize() const
{
     if (_writePtr < _readPtr)
       return (_len - _readPtr + _writePtr);
     return (_writePtr - _readPtr);
}

void CircularBuffer::append(const void *ptr, unsigned int size)
{
    if (!ptr)
        return ;
    for (unsigned i = 0; i < size; ++i)
      {
        _buf[_writePtr % _len] = ((char *) ptr)[i];
        _writePtr++;
        if (_writePtr == _readPtr)
          {
            ++_readPtr;
            _readPtr %= _len;
          }
      }
    _writePtr %= _len;
    _readPtr %= _len;
}

bool CircularBuffer::hasCharacter(const char c) const
{
   int i;

    for (i = _readPtr; i != _writePtr; ++i, i %= _len)
    {
      if (_buf[i] == c)
        return (true);
    }
  return (false);
}

unsigned int CircularBuffer::extract(void *buffer, unsigned int maxSize, const char delim)
{
    unsigned int i;

    if (!buffer)
        return (0);
     _readPtr %= _len;
     for (i = 0; i < maxSize && _readPtr != _writePtr;
          ++_readPtr, _readPtr %= _len, ++i)
       {
         ((char *)buffer)[i] = _buf[_readPtr];
         if (_buf[_readPtr] == delim && delim != -1)
           {
             ++(_readPtr);
             _readPtr %= _len;
             return (i + 1);
           }
       }
     return (i);
}

char CircularBuffer::getByte()
{
    char  c;

    if (_writePtr == _readPtr)
      return (0);
    c = _buf[_readPtr];
    ++(_readPtr);
    _readPtr %= _len;
    return (c);
}

bool CircularBuffer::isEmpty() const
{
    if (_readPtr == _writePtr)
       return (1);
     return (0);
}

unsigned int CircularBuffer::dropBack(unsigned int size)
{
    unsigned int rsize;

    rsize = CircularBuffer::getReadSize();
    if (size <= rsize)
      {
        _readPtr += size;
        _readPtr %= _len;
      }
    else
      _readPtr = _writePtr;
    return (CircularBuffer::getReadSize());
}

unsigned int CircularBuffer::extractKeep(void *buffer, unsigned int maxSize, const char delim)
{
    unsigned int i;
    int buf_read_bak;

    if (!buffer)
        return (0);
    buf_read_bak = _readPtr;
    for (i = 0; i < maxSize && _readPtr != _writePtr;
         ++_readPtr, _readPtr %= _len, ++i)
      {
        ((char *)buffer)[i] = _buf[_readPtr];
        if (_buf[_readPtr] == delim && delim != -1)
          {
            ++(_readPtr);
              _readPtr = buf_read_bak;
             return (i + 1);
          }
      }
    _readPtr = buf_read_bak;
    return (i);
}

unsigned int CircularBuffer::restore(unsigned int size)
{
     int i;

     size %= _len;
     for (i = _readPtr; i != _writePtr && size; ++i, --size);
     return (size);
}

unsigned int CircularBuffer::drop(unsigned int size)
{
     unsigned int i;
     int j;

     for (i = 0, j = _writePtr; i < size && j != _readPtr; i++)
       {
         j--;
         if (j < 0)
           j += _len;
       }
     _writePtr = j;
     return (i);
}


