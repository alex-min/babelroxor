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
#include "connectionlogine.h"
#include "protocolinterfaceslot.h"
#include "audiothread.h"

class ListenServer : public QThread
{
    Q_OBJECT

signals:
    void    connected();
    void    warningPopUp(QString const&, QString const&);
    void    contactStatusChanged(QString const &, int);
    void    successPopUp(QString const &, QString const &);

public:
    ListenServer();
    void    run();
    void    emitConnected();
    void    emitWarningPopUp(std::string const &title, std::string const &text);
    void    emitSuccessPopUp(std::string const &title, std::string const &text);
    void    emitContactStatusChanged(std::string const &login, int status);
    virtual ~ListenServer();

public slots:
    void    addNewClient(QString const &login);
    void    updateClientStatus(QString const &login, int status);
    void    createAccount(QString const &login, QString const &password);
    void    createNewLink(QString const &login);

private:
    PortableNetworkManager _networkManager;
    bool                   _connection;
    AudioThread _t;

};

typedef Singleton<ListenServer> ListenServerSingleton;

#endif // LISTENSERVER_H
