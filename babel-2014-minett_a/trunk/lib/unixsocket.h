#ifndef UNIXSOCKET_H
#define UNIXSOCKET_H
#include "iportablesocket.h"
#ifdef OS_UNIX
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/resource.h>


class UNIXSocket : public APortableSocket
{
public:
    UNIXSocket();
    virtual bool connect(std::string const & remote, unsigned int port, SockType type = TCP);
    virtual UNIXSocket *waitForClient();
    virtual void setMaxClient(unsigned int nb);
    virtual unsigned int getNumberConnectedClient() const;
    virtual unsigned int getTotalNumberConnectedClient() const;
    virtual void send(std::string const &str);
    virtual void send(const char *str, unsigned int len);
    virtual void send(IPortableSocket *sock, std::string const & str);
    virtual void send(IPortableSocket *sock, char *str, unsigned int len);
    // return : size of byte written in buf
    virtual unsigned int read(char *buf, unsigned int size);
    // return : size of byte written in buf
    virtual unsigned int read(IPortableSocket *sock, char *buf, unsigned int size);
    virtual void disconnect();
    virtual bool isServerSock() const;
    virtual bool createServerSocket(IPortableSocket::SockType type, unsigned int port);
    std::string const &getIp() const;
    virtual unsigned short getPort() const;

 public:
    int UNIXGetSocket() const;

private:
    UNIXSocket(int sock, struct sockaddr_in sin, unsigned short port);

private:
    bool createClientSock();

protected:
    int _sock;
    struct sockaddr_in _sin;
    bool _isServerSock;
    std::string _ip;
    char _ipbuf[30];
};

#endif
#endif // UNIXSOCKET_H
