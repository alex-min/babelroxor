#ifndef ISPEEXDECODE_H
#define ISPEEXDECODE_H


class ISpeexdecode
{
public:
    virtual ~ISpeexdecode() {};
    virtual short *Decode(char *bitsToDecode, unsigned int size) = 0;
};

#endif // ISPEEXDECODE_H
