#include "windowsnetworkmanager.h"
#include "accountmanager.h"
#ifdef OS_WINDOWS

Win32NetworkManager::Win32NetworkManager() :
    _maxfd(-1),
    _mainBuffer(new char[4096])
{
}

void Win32NetworkManager::generateReadFs()
{
    FD_ZERO(&_readfs);
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        FD_SET((*it)->getSocket()->Win32GetSocket(), &_readfs);
    }
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

void Win32NetworkManager::addNetwork(Network *network)
{
    if (network && network->getSocket())
    {
        _network.push_back(network);
        if (network->getSocket()->Win32GetSocket() > _maxfd)
        _maxfd = network->getSocket()->Win32GetSocket();
     Win32NetworkManager::generateReadFs();
    }
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
    timeout.tv_usec = uTimeout  *1000;
    Win32NetworkManager::generateWriteFs();
    unsigned int size;

    Win32NetworkManager::generateReadFs();
    ::memcpy(&_readfscpy, &_readfs, sizeof(fd_set));
    if (::select(_maxfd + 1, &_readfs, (_hasWriteFs == true) ? &_writefs : NULL, NULL,
                 (uTimeout == -1) ? NULL : &timeout) == -1)
    {
        return ;
    }
    for (std::list<Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if ((*it)->getSocket() && FD_ISSET((*it)->getSocket()->Win32GetSocket(), &_readfs))
        {
            if ((*it)->getSocket()->isServerSock())
            {
                std::cout << "Waiting for client" << std::endl;
                Network *n = new Network((*it)->getSocket()->waitForClient());
                Win32NetworkManager::addNetwork(n);
                Protocol::getInstance()->welcomeEvent(n);
                if ((*it)->getName() != "") {
                    std::cout << "NETWORKMANAGER:Registering with " << (*it)->getName() << " and net=" << n << std::endl;
                    NetworkRouteSingleton::getInstance()->registerRoute((*it)->getName(), n, false);
                }
                return ;
            } else {
                try {
            size = (*it)->getSocket()->read(_mainBuffer, 512);
            if (size == 0)
            {
                std::cout << "client disconnected" << std::endl;
                (*it)->getSocket()->disconnect();
                if (AccountManagerSingleton::getInstance()->getAccountFromLogin(
                            AccountManagerSingleton::getInstance()->getLoginFromNetwork(*it)) != NULL)
                    AccountManagerSingleton::getInstance()->getAccountFromLogin(
                                AccountManagerSingleton::getInstance()->getLoginFromNetwork(*it))->setConnected(false);
                NetworkRouteSingleton::getInstance()->eraseRoute(
                            AccountManagerSingleton::getInstance()->getLoginFromNetwork(*it));
                AccountManagerSingleton::getInstance()->removeNetwork(*it);
                _network.erase(it);
                std::cout << _network.size() << " sockets remaining..." << std::endl;
                Win32NetworkManager::generateReadFs();
                return ;
            }
            else
            {
                (*it)->getReadBuffer()->append(_mainBuffer, size);
                Protocol::getInstance()->readEvent(*it);
            }
                } catch (std::exception e) {
                }
            }
        }
        else if ((*it)->getSocket() && FD_ISSET((*it)->getSocket()->Win32GetSocket(), &_writefs))
        {
            std::cout << "Win32NetworkManager::writing..." << std::endl;

            size = (*it)->getWriteBuffer()->extract(_mainBuffer, 512);
            std::cout << "Win32NetworkManager::after_extract" << std::endl;
            if ((*it)->getSocket()) {
             (*it)->getSocket()->send(_mainBuffer, size);
            }
            std::cout << "Win32NetworkManager::after_send" << std::endl;

        }
    }
}



#endif
