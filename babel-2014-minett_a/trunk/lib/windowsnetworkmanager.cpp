#include "windowsnetworkmanager.h"
#ifdef OS_WINDOWS

Win32NetworkManager::Win32NetworkManager()
{
    this->_maxfd = -1;
    this->_mainBuffer = new char[4096];
}

void Win32NetworkManager::addNetwork(Network *network)
{
    _network.push_back(network);
    if (network->getSocket()->Win32GetSocket() > _maxfd)
        _maxfd = network->getSocket()->Win32GetSocket();
    Win32NetworkManager::generateReadFs();
}

void Win32NetworkManager::removeNetwork(Network *network)
{
    _network.remove(network);
    network->getSocket()->disconnect();
}

void Win32NetworkManager::run(long uTimeout)
{
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = uTimeout;
    Win32NetworkManager::generateWriteFs();
    unsigned int size;

    memcpy(&_readfscpy, &_readfs, sizeof(fd_set));
    if (select(this->_maxfd + 1, &_readfscpy, (_hasWriteFs == true) ? &_writefs : NULL, NULL,
               (uTimeout == -1) ? NULL : &timeout) == SOCKET_ERROR)
        throw std::string("select function failed");
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if (FD_ISSET((*it)->getSocket()->Win32GetSocket(), &_readfscpy))
        {
            if ((*it)->getSocket()->isServerSock() && (*it)->getSocket()->getType() == IPortableSocket::TCP)
            {
              Network *n = new Network((*it)->getSocket()->waitForClient());
              Win32NetworkManager::addNetwork(n);
              Protocol::getInstance()->welcomeEvent(n);
              return ;
            }
            if (size == 0)
                {
                (*it)->getSocket()->disconnect();
                _network.erase(it);
                Win32NetworkManager::generateReadFs();
                return ;
                }
            else
                {
                (*it)->getReadBuffer()->append(_mainBuffer, size);
                Protocol::getInstance()->readEvent(*it);
                }
        }
        else if (FD_ISSET((*it)->getSocket()->Win32GetSocket(), &_writefs))
        {
            size = (*it)->getWriteBuffer()->extract(_mainBuffer, 512);
            (*it)->getSocket()->send(_mainBuffer, size);
        }
    }
}

void Win32NetworkManager::setProtocol(Protocol *protocol)
{
    _protocol = protocol;
}

void Win32NetworkManager::generateReadFs()
{
    FD_ZERO(&_readfs);
    std::list<Network *>::iterator it = _network.begin();
    for ( ; it != _network.end(); ++it)
        FD_SET((*it)->getSocket()->Win32GetSocket(), &_readfs);
}

void Win32NetworkManager::generateWriteFs()
{
    _hasWriteFs = false;
    FD_ZERO(&_writefs);
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if (!((*it)->getWriteBuffer()->isEmpty()))
        {
            _hasWriteFs = true;
            FD_SET((*it)->getSocket()->Win32GetSocket(), &_writefs);
        }
    }
}

#endif
