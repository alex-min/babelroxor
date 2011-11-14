#ifndef IPORTABLESOCKET_H
#define IPORTABLESOCKET_H
#include "portablelibrary.h"
#include <string>

class IPortableSocket
{
public:
    enum SockType {TCP, UDP};
    virtual bool connect(std::string const & remote, unsigned int port, SockType type = TCP) = 0;
    virtual bool createServerSocket(unsigned int port) = 0;
    virtual IPortableSocket *waitForClient() = 0;
    virtual void setMaxClient(unsigned int nb) = 0;
    virtual unsigned int getTotalNumberConnectedClient() const = 0;
    virtual unsigned int getNumberConnectedClient() const = 0;
    virtual void send(std::string const &str) = 0;
    virtual void send(const char *str, unsigned int len) = 0;
    virtual void send(IPortableSocket *sock, std::string const & str) = 0;
    virtual void send(IPortableSocket *sock, char *str, unsigned int len) = 0;
    // return : size of byte written in buf
    virtual unsigned int read(char *buf, unsigned int size) = 0;
    // return : size of byte written in buf
    virtual unsigned int read(IPortableSocket *sock, char *buf, unsigned int size) = 0;
    virtual void disconnect() = 0;
    virtual bool isServerSock() const = 0;
    virtual std::string const &getIp() const = 0;
    virtual unsigned short getPort() const = 0;

};

class APortableSocket : public IPortableSocket
{
public:

protected:
    SockType    _type;
    static int _total_client_connected;
    int _client_connected;
    int _max_client;
    unsigned short _port;
};

#ifdef OS_WINDOWS
#include "win32socket.h"
typedef class Win32Socket PortableSocket;
#elif defined OS_UNIX
#include "unixsocket.h"
typedef class UNIXSocket PortableSocket;
#endif

#endif // IPORTABLESOCKET_H
