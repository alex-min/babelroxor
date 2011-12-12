#include "unixsocket.h"
#ifdef OS_UNIX

 int APortableSocket::_total_client_connected = 0;


UNIXSocket::UNIXSocket()
{
   _sock = -1;
   _max_client = 200;
   _client_connected = 0;
   _isServerSock = false;
   _port = 0;
}

bool UNIXSocket::isServerSock() const
{
    return (_isServerSock);
}

void UNIXSocket::disconnect()
{
    std::cout << "UNIXSocket::disconnect()" << std::endl;
    if (_sock != -1)
          close(_sock);
}

int UNIXSocket::UNIXGetSocket() const
{
    return (_sock);
}

unsigned short UNIXSocket::getPort() const
{
    return (_port);
}


unsigned int UNIXSocket::read(char *buf, unsigned int size)
{
    int rd;
    rd = ::recv(_sock, buf, size, MSG_DONTWAIT);
    if (rd == -1)
        throw std::exception();
    return (rd);
}

unsigned int UNIXSocket::read(IPortableSocket *sock, char *buf, unsigned int size)
{
    UNIXSocket *cl = reinterpret_cast<UNIXSocket *> (sock);
    if (!cl)
        return (0);
    int rd;
    rd = ::recv(cl->_sock, static_cast<void *>(buf), size, 0);
    if (rd == -1)
        return (0);
    return (rd);
}

void UNIXSocket::send(IPortableSocket *sock, std::string const & str)
{
    UNIXSocket::send(sock, const_cast<char *>(str.c_str()), str.length());
}

void UNIXSocket::send(IPortableSocket *sock, char *str, unsigned int len)
{
    UNIXSocket *convert = reinterpret_cast<UNIXSocket *> (sock);
    ::send(convert->_sock, str, len, 0);
}

void UNIXSocket::send(std::string const &str)
{
    UNIXSocket::send(str.c_str(), str.length());
}

UNIXSocket::UNIXSocket(int sock, struct sockaddr_in sin, unsigned short port)
{
    _sock = sock;
    _sin = sin;
    _ip.assign(::inet_ntoa(_sin.sin_addr));
    _port = port;
    _isServerSock = false;
}

void UNIXSocket::send(const char *str, unsigned int len)
{
    if (_sock != -1)
    ::send(_sock, str, len, 0);
}

void UNIXSocket::setMaxClient(unsigned int nb)
{
    _max_client = nb;
}

bool UNIXSocket::createServerSocket(IPortableSocket::SockType type, unsigned int port)
{
    int         enable;

    _isServerSock = true;
    enable = 1;
    if (type == IPortableSocket::UDP && ::getprotobyname("udp"))
        _sock = socket(AF_INET, SOCK_DGRAM, ::getprotobyname("udp")->p_proto);

        _sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    if (_sock == -1)
      {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
      }
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(port);
    _sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(_sock, (struct sockaddr*) &_sin, sizeof(struct sockaddr_in)) == -1
        || listen(_sock, 42) == -1)
      {
         std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
      }
    _ip.assign(::inet_ntoa(_sin.sin_addr));
   return (true);
}

bool UNIXSocket::createClientSock()
{
    _isServerSock = false;
     if (_sock > 0)
         close(_sock);
     _sock = socket(AF_INET, SOCK_STREAM, 0);
     if (_sock < 0)
         return (false);
     std::cout << "[+] Connecting..." << std::endl;
     if (::connect(_sock, (sockaddr *) &_sin, sizeof(_sin)) == -1)
     {
          std::cout << "[-] Connection failed" << std::endl;
          return (false);
     }
     std::cout << "[+] Connection successfull" << std::endl;
     _ip.assign(::inet_ntoa(_sin.sin_addr));
     return (true);
}

bool UNIXSocket::connect(std::string const & remote, unsigned int port,
             IPortableSocket::SockType type)
{

     struct hostent * record = gethostbyname(remote.c_str());
     if (!record)
         return (false);
     in_addr * address = (in_addr * )record->h_addr;
     char * ip_address = inet_ntoa(* address);

     std::cout << "[+] Server found at " << ip_address << std::endl;

     _sin.sin_addr.s_addr = inet_addr(ip_address);
     _sin.sin_family = AF_INET;
     _sin.sin_port = htons(port);
     //_sin.sin_addr.s_addr = INADDR_ANY;
     _type = type;
    bool ret = UNIXSocket::createClientSock();
    if (ret)
        _port = port;
    return (ret);
}

UNIXSocket * UNIXSocket::waitForClient()
{
     struct rlimit         l;
     int                   csock;
     int                   client_sin_len;
     struct sockaddr_in client_sin;

     getrlimit(RLIMIT_NOFILE, &l);
     client_sin_len = sizeof(struct sockaddr_in);
     csock = accept(_sock, (struct sockaddr *) &client_sin,
                    (socklen_t *) &client_sin_len);
     if ((static_cast<unsigned int>(_client_connected) + 10) >= l.rlim_cur ||
         _client_connected == _max_client)
       {
             close(csock);
             return (NULL);
       }
    //_client_connected++;
    return (new UNIXSocket(csock, client_sin, _port));
}

unsigned int UNIXSocket::getNumberConnectedClient() const
{
    return (_client_connected);
}

unsigned int UNIXSocket::getTotalNumberConnectedClient() const
{
    return (_total_client_connected);
}

std::string const &UNIXSocket::getIp() const
{
    return (_ip);
}

#endif
