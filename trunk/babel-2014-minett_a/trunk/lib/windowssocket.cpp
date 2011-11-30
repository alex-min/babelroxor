#include "windowssocket.h"
#ifdef OS_WINDOWS

WSADATA Win32Socket::_wsaData = {0};
bool Win32Socket::_init = false;
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

bool Win32Socket::createServerSocket(IPortableSocket::SockType type, unsigned int port)
{

    this->_isServerSock = true;
    Win32Socket::WSAInit();

    this->_type = type;
    if (type == TCP)
        this->_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    else if (type == UDP)
        this->_sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (this->_sock == INVALID_SOCKET)
    {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
    }
    this->_sin.sin_family = AF_INET;
    this->_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    this->_sin.sin_port = htons((unsigned short)port);
    if (bind(this->_sock, (SOCKADDR *) &this->_sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
    }
    if (type != UDP && listen(this->_sock, 42) == SOCKET_ERROR)
    {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
    }
    return (true);
}

bool Win32Socket::createClientSocket()
{
    Win32Socket::WSAInit();
    this->_isServerSock = false;
    if (this->_sock != INVALID_SOCKET)
        closesocket(this->_sock);
    Win32Socket::WSAInit();
    if (_type == TCP)
        this->_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    else if (_type == UDP)
        this->_sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (this->_sock == INVALID_SOCKET)
        return (false);
    std::cout << "[+] Connecting..." << std::endl;
    if (_type == TCP && WSAConnect(this->_sock, (SOCKADDR *) &this->_sin, sizeof(this->_sin), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
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

void Win32Socket::WSAInit()
{
    if (_init == false)
    {
        if ((WSAStartup(MAKEWORD(2, 2), &_wsaData)) != 0)
        {
            std::cout << "[-] Cannot initialize WSAStartup" << std::endl;
        }
        _init = true;
    }
}

bool Win32Socket::connect(std::string const & remote, unsigned int port, SockType type)
{
    Win32Socket::WSAInit();
    struct hostent * record = ::gethostbyname(remote.c_str());
    std::cout << "Connecting... to " << remote << " at " << port <<  std::endl;
    if (!record)
        return (false);
    std::cout << "HERE" << std::endl;
    in_addr * address = (in_addr * )record->h_addr;
    char * ip_address = inet_ntoa(* address);

    std::cout << "[+] Server found at " << ip_address << std::endl;

    this->_sin.sin_addr.s_addr = inet_addr(ip_address);
    this->_sin.sin_family = AF_INET;
    this->_sin.sin_port = ::htons(port);
    // Because WSAHTons don't work at all...
    // WSAHtons(this->_sock, static_cast<short>(port), &(this->_sin.sin_port));
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
    if (this->_sock != INVALID_SOCKET && this->_type == TCP)
        WSASend(this->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL);
    else if (this->_sock != INVALID_SOCKET && this->_type == UDP)
        WSASendTo(this->_sock, &DataBuf, 1, &SendBytes, 0, (SOCKADDR *) &this->_sin, sizeof(this->_sin), NULL, NULL);
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
    if (convert->_sock != INVALID_SOCKET && this->_type == TCP)
        WSASend(convert->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL);
    else if (convert->_sock != INVALID_SOCKET && this->_type == UDP)
        WSASendTo(convert->_sock, &DataBuf, 1, &SendBytes, 0, (SOCKADDR *) &this->_sin, sizeof(this->_sin), NULL, NULL);
}

// return : size of byte written in buf
unsigned int Win32Socket::read(char *buf, unsigned int size)
{
    int     ret;
    WSABUF  DataBuf;
    DWORD   SendBytes;

    DataBuf.buf = buf;
    DataBuf.len = size;
    if (this->_type == TCP)
        ret = WSARecv(this->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL);
    else if (this->_type == UDP)
    {
        SOCKADDR_IN sender;
        int tmp = sizeof(SOCKADDR_IN);
        DWORD flags = 0;
        ret = WSARecvFrom(this->_sock, &DataBuf, 1, &SendBytes, &flags, (SOCKADDR *) &sender, &tmp, NULL, NULL);
    }
    if (ret == SOCKET_ERROR)
        return (0);
    std::cout << buf << std::endl;
    return (SendBytes);
}

// return : size of byte written in buf
unsigned int Win32Socket::read(IPortableSocket *sock, char *buf, unsigned int size)
{
    int     ret;
    WSABUF  DataBuf;
    DWORD   SendBytes;

    DataBuf.buf = buf;
    DataBuf.len = size;
    Win32Socket *convert = reinterpret_cast<Win32Socket *> (sock);
    if (!convert)
        return 0;
    if (this->_type == TCP)
        ret = WSARecv(convert->_sock, &DataBuf, 1, &SendBytes, 0, 0, NULL);
    else if (this->_type == UDP)
    {
        SOCKADDR_IN sender;
        int tmp = sizeof(SOCKADDR_IN);
        DWORD flags = 0;
        ret = WSARecvFrom(convert->_sock, &DataBuf, 1, &SendBytes, &flags, (SOCKADDR *) &sender, &tmp, NULL, NULL);
    }
    if (ret == SOCKET_ERROR)
        return (0);
    return (SendBytes);
}

std::string const &Win32Socket::getIp() const
{
    return (_ip);
}

unsigned short Win32Socket::getPort() const
{
    return (_port);
}

IPortableSocket::SockType    Win32Socket::getType() const
{
    return (_type);
}

#endif
