#include "unixnetworkmanager.h"
#ifdef OS_UNIX

UNIXNetworkManager::UNIXNetworkManager() :
    _maxfd(-1),
    _mainBuffer(new char[4096])
{
}

void UNIXNetworkManager::generateReadFs()
{
    FD_ZERO(&_readfs);
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        FD_SET((*it)->getSocket()->UNIXGetSocket(), &_readfs);
    }
}

void UNIXNetworkManager::generateWriteFs()
{
    _hasWriteFs = false;
    FD_ZERO(&_writefs);
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if (!((*it)->getWriteBuffer()->isEmpty()))
        {
            _hasWriteFs = true;
            FD_SET((*it)->getSocket()->UNIXGetSocket(), &_writefs);
        }
    }
}

void UNIXNetworkManager::addNetwork(Network *network)
{
    _network.push_back(network);
    if (network->getSocket()->UNIXGetSocket() > _maxfd)
        _maxfd = network->getSocket()->UNIXGetSocket();
    UNIXNetworkManager::generateReadFs();
}

void UNIXNetworkManager::removeNetwork(Network *network)
{
    _network.remove(network);
    network->getSocket()->disconnect();
}

void UNIXNetworkManager::run(long uTimeout)
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = uTimeout;
    UNIXNetworkManager::generateWriteFs();
    unsigned int size;

    ::memcpy(&_readfscpy, &_readfs, sizeof(fd_set));
    if (::select(_maxfd + 1, &_readfscpy, (_hasWriteFs == true) ? &_writefs : NULL, NULL,
                 (uTimeout == -1) ? NULL : &timeout) == -1)
    {
        throw std::string("select function failed");
    }
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if (FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_readfscpy))
        {
            if ((*it)->getSocket()->isServerSock())
            {
              Network *n = new Network((*it)->getSocket()->waitForClient());
              UNIXNetworkManager::addNetwork(n);
              _protocol->welcomeEvent(n);
              return ;
            }
            size = (*it)->getSocket()->read(_mainBuffer, 512);
            if (size == 0)
            {
                (*it)->getSocket()->disconnect();
                _network.erase(it);
                UNIXNetworkManager::generateReadFs();
                return ;
            }
            else
               {
                   std::cout << size << std::endl;
                (*it)->getReadBuffer()->append(_mainBuffer, size);
                _protocol->readEvent(*it);
               }
        }
        else if (FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_writefs))
        {
            size = (*it)->getWriteBuffer()->extract(_mainBuffer, 512);
            (*it)->getSocket()->send(_mainBuffer, size);
        }
    }
}

void UNIXNetworkManager::setProtocol(Protocol *protocol)
{
    _protocol = protocol;
}

#endif
