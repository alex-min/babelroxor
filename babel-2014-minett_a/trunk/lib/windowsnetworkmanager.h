#ifndef WINDOWSNETWORKMANAGER_H
#define WINDOWSNETWORKMANAGER_H
#include "inetworkmanager.h"
#ifdef OS_WINDOWS

class Win32NetworkManager : public INetworkManager
{
public:
    Win32NetworkManager();
    virtual void addNetwork(Network *network);
    virtual void removeNetwork(Network *network);
    virtual void run(long uTimeout = -1);
    virtual void setProtocol(Protocol *protocol);


private:
    void generateReadFs();
    void generateWriteFs();

private:
    fd_set  _readfs;
    fd_set  _writefs;
    fd_set  _readfscpy;
    std::list<Network *> _network;
    int     _maxfd;
    bool    _hasWriteFs;
    char    *_mainBuffer;
};

#endif
#endif // WINDOWSNETWORKMANAGER_H
