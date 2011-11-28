#include "windowssocket.h"
#ifdef OS_WINDOWS

int APortableSocket::_total_client_connected = 0;

Win32Socket::Win32Socket()
{
    _sock = INVALID_SOCKET;
    _max_client = 200;
    _client_connected = 0;
    _isServerSock = false;
    _port = 0;
}

Win32Socket::Win32Socket(SOCKET sock, SOCKADDR_IN sin, unsigned short port)
{
    _sock = sock;
    _sin = sin;
    _ip.assign(inet_ntoa(_sin.sin_addr));
    _port = port;
}

int Win32Socket::Win32GetSocket() const
{
    return (this->_sock);
}

bool Win32Socket::createServerSocket(unsigned int port)
{
    WSADATA wsaData = {0};

    this->_isServerSock = true;
    if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        std::cout << "[-] Cannot initialize WSAStartup" << std::endl;
        return (false);
    }
    this->_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, NULL);
    if (this->_sock == INVALID_SOCKET)
    {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
    }
    this->_sin.sin_family = AF_INET;
    WSAHtonl(this->_sock, INADDR_ANY, &this->_sin.sin_addr.s_addr);
    WSAHtons(this->_sock, port, &this->_sin.sin_port);
    if (bind(this->_sock, (SOCKADDR *) &this->_sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
    }
    if (listen(this->_sock, 42) == SOCKET_ERROR)
    {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
    }
    return (true);
}

bool Win32Socket::createClientSocket()
{
    WSADATA wsaData = {0};

    this->_isServerSock = false;
    if (this->_sock != INVALID_SOCKET)
        closesocket(this->_sock);
    if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        std::cout << "[-] Cannot initialize WSAStartup" << std::endl;
        return (false);
    }
    this-> _sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (this->_sock == INVALID_SOCKET)
        return (false);
    std::cout << "[+] Connecting..." << std::endl;
    if (WSAConnect(this->_sock, (SOCKADDR *) &this->_sin, sizeof(this->_sin), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
    {
        std::cout << "[-] Connection failed" << std::endl;
        return (false);
    }
    std::cout << "[+] Connection successfull" << std::endl;
    return (true);
}

bool Win32Socket::isServerSock() const
{
    return (_isServerSock);
}

void Win32Socket::disconnect()
{
    if (_sock != INVALID_SOCKET)
    {
        closesocket(this->_sock);
        WSACleanup();
    }
}

bool Win32Socket::connect(std::string const & remote, unsigned int port, SockType type)
{
    struct hostent * record = gethostbyname(remote.c_str());
    if (!record)
        return (false);
    in_addr * address = (in_addr * )record->h_addr;
    char * ip_address = inet_ntoa(* address);

    std::cout << "[+] Server found at " << ip_address << std::endl;

    this->_sin.sin_addr.s_addr = inet_addr(ip_address);
    this->_sin.sin_family = AF_INET;
    WSAHtons(this->_sock, port, &this->_sin.sin_port);
    this->_type = type;
    return (Win32Socket::createClientSocket());
}

Win32Socket *Win32Socket::waitForClient()
{
    SOCKET                  csock;
    SOCKADDR_IN             client_sin;
    int                     client_sin_len;

    client_sin_len = sizeof(client_sin);
    csock = WSAAccept(this->_sock, (SOCKADDR *) &client_sin, &client_sin_len, NULL, NULL);
    if (this->_client_connected >= this->_max_client)
      {
            closesocket(csock);
            return (NULL);
      }
   this->_client_connected++;
   return (new Win32Socket(csock, client_sin, _port));
}

void Win32Socket::setMaxClient(unsigned int nb)
{
    this->_max_client = nb;
}

unsigned int Win32Socket::getNumberConnectedClient() const
{
    return this->_client_connected;
}

unsigned int Win32Socket::getTotalNumberConnectedClient() const
{
    return this->_total_client_connected;
}

void Win32Socket::send(std::string const &str)
{
    Win32Socket::send(str.c_str(), str.length());
}

void Win32Socket::send(const char *str, unsigned int len)
{
    WSABUF  DataBuf;
    DWORD   SendBytes;

    DataBuf.len = len;
    DataBuf.buf = const_cast<char *> (str);
    if (this->_sock != INVALID_SOCKET)
        WSASend(this->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL);
}

void Win32Socket::send(IPortableSocket *sock, std::string const & str)
{
    Win32Socket::send(sock, const_cast<char *> (str.c_str()), str.length());
}

void Win32Socket::send(IPortableSocket *sock, char *str, unsigned int len)
{
    WSABUF  DataBuf;
    DWORD   SendBytes;

    DataBuf.len = len;
    DataBuf.buf = str;
    Win32Socket *convert = reinterpret_cast<Win32Socket *> (sock);
    if (!convert)
        return ;
    if (this->_sock != INVALID_SOCKET)
        WSASend(convert->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL);
}

// return : size of byte written in buf
unsigned int Win32Socket::read(char *buf, unsigned int size)
{
    WSABUF  DataBuf;
    DWORD   SendBytes;

    DataBuf.buf = buf;
    DataBuf.len = size;
    return (WSARecv(this->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL));
}

// return : size of byte written in buf
unsigned int Win32Socket::read(IPortableSocket *sock, char *buf, unsigned int size)
{
    WSABUF  DataBuf;
    DWORD   SendBytes;

    DataBuf.buf = buf;
    DataBuf.len = size;
    Win32Socket *convert = reinterpret_cast<Win32Socket *> (sock);
    if (!convert)
        return 0;
    return (WSARecv(convert->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL));
}

std::string const &Win32Socket::getIp() const
{
    return (_ip);
}

unsigned short Win32Socket::getPort() const
{
    return (_port);
}

#endif
