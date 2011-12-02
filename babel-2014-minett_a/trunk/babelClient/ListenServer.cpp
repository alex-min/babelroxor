#include "ListenServer.h"
#include "audiothread.h"
#include "CentralWidget.h"
#include "requestlink.h"
#include "connecttome.h"
#include <QCoreApplication>

#include "ListenServer.h"
#include "audiothread.h"
#include "DockWidgetContent.h"
#include "status.h"
#include "StatusAnswer.h"
#include "Account.h"

ListenServer::ListenServer()
{
    Network *net = new Network;
    Protocol *proto = Protocol::getInstance();
    ConnectionSlot *c = new ConnectionSlot;
    ProxySlot *p = new ProxySlot;
    proto->registerSlot(Protocol::AUDIO, AudioSlotSingle::getInstance());
    proto->registerSlot(Protocol::CONNECTION, ProtocolInterfaceSlot::getInstance());
    proto->registerSlot(Protocol::PROXY_FORWARD, p);
    proto->registerSlot(Protocol::TEST_CONNECTION, TestConnectionSingleton::getInstance());
    proto->registerSlot(Protocol::PROXY_RECEIVED, ProxyReceivedSlotSingleton::getInstance());
    proto->registerSlot(Protocol::REQUEST_STATUS, StatusAnswerSingleton::getInstance());
    proto->registerSlot(Protocol::CONNECT_TO_ME, ConnectToMe::getInstance());
    proto->registerSlot(Protocol::CALL, CallAnswerSingleton::getInstance());

    std::cout << "Connecting {{---}}" << std::endl;
    if (!net->getSocket()->connect("127.0.0.1", 4646))
        _connection = false;
    else
        _connection = true;

    Protocol::getInstance()->defaultGateway(net);
    _networkManager.addNetwork(net);

    connect(DockWidgetContentSingleton::getInstance(), SIGNAL(newClient(QString const &)), this, SLOT(addNewClient(QString const &)));
    connect(DockWidgetContentSingleton::getInstance(), SIGNAL(clientStatus(QString const&, int)), this, SLOT(updateClientStatus(QString const&, int)));
    connect(AccountSingleton::getInstance(), SIGNAL(accountCreation(QString const&,QString const&)), this, SLOT(createAccount(QString const&, QString const&)));
    connect(CentralWidgetSingleton::getInstance(), SIGNAL(newLink(QString const &)), this, SLOT(createNewLink(QString const &)));
}

void    ListenServer::emitCallFail()
{
    emit callFail();
}

void    ListenServer::emitCall(std::string const &login, unsigned int id)
{
    emit callOccured(QString(login.c_str()), id);
}

void    ListenServer::createAccount(QString const &login, QString const &password)
{
    ConnectionLoginSingleton::getInstance()->registerAccount(login.toStdString(), password.toStdString());
}

void    ListenServer::emitContactStatusChanged(std::string const &login, int status)
{
    emit contactStatusChanged(QString(login.c_str()), status);
}

void    ListenServer::updateClientStatus(QString const &login, int status)
{
    StatusSingleton::getInstance()->updateStatus(login.toStdString(), status);
}

void    ListenServer::addNewClient(QString const &login)
{
    StatusSingleton::getInstance()->requestStatus(login.toStdString());
}

void    ListenServer::createNewLink(QString const &login)
{
    RequestLinkSingleton::getInstance()->createNewLink(login.toStdString());
}

void    ListenServer::run(void)
{
    //    AudioThread t;
    //  t.start();
    if (!_connection)
        return;

    //    AudioThreadSingleton::getInstance()->start();

    while (1)
    {
        _networkManager.run(TimerPoolSingleton::getInstance()->getMsNextCall());
        TimerPoolSingleton::getInstance()->autocall();
    }

    std::cout << "Exiting" << std::endl;
}
void    ListenServer::emitWarningPopUp(std::string const &title, std::string const &text)
{
    emit warningPopUp(QString(title.c_str()), QString(text.c_str()));
}

void    ListenServer::emitSuccessPopUp(std::string const &title, std::string const &text)
{
    emit successPopUp(QString(title.c_str()), QString(text.c_str()));
}

void    ListenServer::emitConnected()
{
    std::cout << "C'est bon !!" << std::endl;
    AudioThreadSingleton::getInstance()->addLogin("lol");
    std::cout << "C'est bon !!" << std::endl;
    emit connected();
}

ListenServer::~ListenServer()
{

}

