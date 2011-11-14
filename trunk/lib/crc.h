#ifndef CRC_H
#define CRC_H
#define POLY 0x8408

class CRC
{
public:
    static unsigned short getCRC16(void *data, unsigned short len);
};

#endif // CRC_H
