#ifndef LISTENSERVER_H
#define LISTENSERVER_H

#include <QThread>

#include "singleton.h"
#include "Thread.h"
#include "iportablesocket.h"
#include "network.h"
#include "inetworkmanager.h"
#include "protocol.h"
#include "audio.h"
#include "connectionslot.h"
#include "proxyslot.h"
#include "testconnection.h"
#include "proxyreceivedslot.h"
#include "requestlink.h"
#include "pool.h"
#include "packet.h"
#include "timerpool.h"
#include "audioslot.h"
#include "connectionlogin.h"
#include "protocolinterfaceslot.h"
#include "StatusAnswer.h"
#include "audiothread.h"

class ListenServer : public QThread
{
    Q_OBJECT

signals:
    void    connected();
    void    connectionPopUpWarning(QString const&, QString const&);

public:
    ListenServer();
    void    run();
    void    emitConnected();
    void    emitConnectionPopUpWarning(std::string const &title, std::string const &text);
    virtual ~ListenServer();
private:
    PortableNetworkManager _networkManager;
    bool                   _connection;
    AudioThread _t;

};

typedef Singleton<ListenServer> ListenServerSingleton;

#endif // LISTENSERVER_H
