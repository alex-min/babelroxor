#ifndef WINDOWSSOCKET_H
#define WINDOWSSOCKET_H
#include "iportablesocket.h"
#ifdef OS_WINDOWS

#include <iostream>
#include <winsock2.h>

class Win32Socket : public APortableSocket
{
public:
    Win32Socket();
    virtual bool connect(std::string const & remote, unsigned int port, SockType type = TCP);
    virtual Win32Socket *waitForClient();
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
    int Win32GetSocket() const;
    SockType    getType() const;
private:
    void WSAInit();

private:
    bool createClientSocket();
    Win32Socket(SOCKET sock, SOCKADDR_IN sin, unsigned short port);

protected:
    SOCKET                      _sock;
    SOCKADDR_IN                 _sin;
    bool                        _isServerSock;
    std::string                 _ip;
    char                        _ipbuf[30];
    static WSADATA _wsaData;
    static bool _init;
};

#endif
#endif // WINDOWSSOCKET_H
