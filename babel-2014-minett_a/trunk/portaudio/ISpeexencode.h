#ifndef ISPEEXENCODE_H
#define ISPEEXENCODE_H


class ISpeexencode
{
public:
    virtual ~ISpeexencode() {};
    virtual  unsigned int	Encode(short *input, char *output) = 0;
};

#endif // ISPEEXENCODE_H
