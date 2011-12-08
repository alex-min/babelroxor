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
    void    callOccured(QString const &, unsigned int);
    void    callFail();
    void    newContactToUpdateList(QString const &);
    void    textMessageChanged(QString const &);
    void    hungUp(QString const &);

public:
    ListenServer();
    void    run();
    void    emitConnected();
    void    emitWarningPopUp(std::string const &title, std::string const &text);
    void    emitSuccessPopUp(std::string const &title, std::string const &text);
    void    emitContactStatusChanged(std::string const &login, int status);
    void    emitCall(std::string const &login, unsigned int id);
    void    emitCallFail();
    void    emitAddContactToUpdateList(std::string const &login);
    void    emitTextMessageChanged(std::string const &text);
    void    emitHungUp(std::string const &contactLogin);

    virtual ~ListenServer();

public slots:
    void    addNewClient(QString const &login);
    void    updateClientStatus(int status, QList<std::string> const &contactUpdateList);
    void    createAccount(QString const &login, QString const &password);
    void    createNewLink(QString const &login);
    void    openTalkWindow(QString const &login);
    void    disconnectClient(QString const &login, QString const &password);
    void    sendText(QString const &login, QString const &text);
    void    hangUp(QString const &senderLogin, QString const &contactLogin);

private:
    bool                   _connection;
    Network                *_net;
    AudioThread _t;
};

typedef Singleton<ListenServer> ListenServerSingleton;

#endif // LISTENSERVER_H
