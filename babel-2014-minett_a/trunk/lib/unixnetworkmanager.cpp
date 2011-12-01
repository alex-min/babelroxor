#include "unixnetworkmanager.h"
#include "accountmanager.h"
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
    timeout.tv_usec = uTimeout  *1000;
    UNIXNetworkManager::generateWriteFs();
    unsigned int size;

    UNIXNetworkManager::generateReadFs();
    ::memcpy(&_readfscpy, &_readfs, sizeof(fd_set));
    if (::select(_maxfd + 1, &_readfs, (_hasWriteFs == true) ? &_writefs : NULL, NULL,
                 (uTimeout == -1) ? NULL : &timeout) == -1)
    {
        return ;
    }
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if (FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_readfs))
        {
            if ((*it)->getSocket()->isServerSock())
            {
                std::cout << "Waiting for client" << std::endl;
                Network *n = new Network((*it)->getSocket()->waitForClient());
                UNIXNetworkManager::addNetwork(n);
                Protocol::getInstance()->welcomeEvent(n);
                return ;
            }
            size = (*it)->getSocket()->read(_mainBuffer, 512);
            if (size == 0)
            {
                std::cout << "client disconnected" << std::endl;
                (*it)->getSocket()->disconnect();
                NetworkRouteSingleton::getInstance()->eraseRoute(
                            AccountManagerSingleton::getInstance()->getLoginFromNetwork(*it));
                AccountManagerSingleton::getInstance()->removeNetwork(*it);
                _network.erase(it);
                std::cout << _network.size() << " sockets remaining..." << std::endl;
                UNIXNetworkManager::generateReadFs();
                return ;
            }
            else
            {
                (*it)->getReadBuffer()->append(_mainBuffer, size);
                Protocol::getInstance()->readEvent(*it);
            }
        }
        else if (FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_writefs))
        {
            std::cout << "UNIXNetworkManager::writing..." << std::endl;

            size = (*it)->getWriteBuffer()->extract(_mainBuffer, 512);
            std::cout << "UNIXNetworkManager::after_extract" << std::endl;
             (*it)->getSocket()->send(_mainBuffer, size);
            std::cout << "UNIXNetworkManager::after_send" << std::endl;
        }
    }
}



#endif
