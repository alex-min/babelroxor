#ifndef NETWORK_H
#define NETWORK_H
#include <map>
#include "iportablesocket.h"
#include "circularbuffer.h"
#include "islotinterface.h"
#include "crc.h"
#include "singleton.h"

class Network
{

public:
    Network(unsigned int readCirbufSize = 4096, unsigned int writeCirbufSize = 4096);
    Network(PortableSocket *sock, unsigned int readCirbufSize = 4096, unsigned int writeCirbufSize = 4096);
    CircularBuffer *getReadBuffer();
    CircularBuffer *getWriteBuffer();
    PortableSocket *getSocket();
    void setSocket(PortableSocket *sock);
    std::string const &getName() const;
    void setName(std::string const &);

protected:
    std::string  _name;
    PortableSocket *_socket;
    CircularBuffer _readBuf;
    CircularBuffer _writeBuf;
};

#endif // NETWORK_H
