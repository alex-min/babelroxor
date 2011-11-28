#ifndef UNIXNetworkManager_H
#define UNIXNetworkManager_H
#include "inetworkmanager.h"
#ifdef OS_UNIX
#include <exception>
#include <sys/select.h>
#include <string.h>
#include "network.h"
#include "networkroute.h"

class UNIXNetworkManager : public INetworkManager
{
public:
    UNIXNetworkManager();
    virtual void addNetwork(Network *network);
    virtual void removeNetwork(Network *network);
    virtual void run(long uTimeout = -1);


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
#endif // UNIXNetworkManager_H
