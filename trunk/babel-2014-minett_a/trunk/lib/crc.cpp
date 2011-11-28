#include "crc.h"

unsigned short CRC::getCRC16(void *data_r, unsigned short length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;
      char *data_p = static_cast<char *>(data_r);

      if (length == 0)
            return (0);
      do
      {
            for (i=0, data= static_cast<unsigned int> (0xff) & *data_p++;
                 i < 8;
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}
