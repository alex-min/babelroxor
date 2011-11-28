#include "network.h"

Network::Network(unsigned int readCirbufSize, unsigned int writeCirbufSize) :
         _socket(new PortableSocket),
        _readBuf(readCirbufSize),
        _writeBuf(writeCirbufSize)
{
}

Network::Network(PortableSocket *sock, unsigned int readCirbufSize, unsigned int writeCirbufSize) :
         _socket(sock),
        _readBuf(readCirbufSize),
        _writeBuf(writeCirbufSize)
{
}

PortableSocket *Network::getSocket()
{
    return (_socket);
}

void Network::setSocket(PortableSocket *sock)
{
    _socket = sock;
}


CircularBuffer *Network::getReadBuffer()
{
    return (&_readBuf);
}

CircularBuffer *Network::getWriteBuffer()
{
    return (&_writeBuf);
}
