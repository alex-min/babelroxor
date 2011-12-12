#include "ListenServer.h"
#include "CentralWidget.h"
#include "requestlink.h"
#include "connecttome.h"
#include <QCoreApplication>
#include "ListenServer.h"
#include "audiothread.h"
#include "DockWidgetContent.h"
#include "status.h"
#include "StatusAnswer.h"
#include "RequestStatusAnswer.h"
#include "Account.h"
#include "MainWindow.h"
#include "TextMessage.h"
#include "TextMessageAnswer.h"
#include "HangUp.h"
#include "HangUpAnswer.h"

ListenServer::ListenServer()
{
    _net = new Network;
    Protocol *proto = Protocol::getInstance();
    ConnectionSlot *c = new ConnectionSlot;
    ProxySlot *p = new ProxySlot;
    proto->registerSlot(Protocol::AUDIO, AudioSlotSingle::getInstance());
    proto->registerSlot(Protocol::CONNECTION, ProtocolInterfaceSlot::getInstance());
    proto->registerSlot(Protocol::PROXY_FORWARD, p);
    proto->registerSlot(Protocol::TEST_CONNECTION, TestConnectionSingleton::getInstance());
    proto->registerSlot(Protocol::PROXY_RECEIVED, ProxyReceivedSlotSingleton::getInstance());
    proto->registerSlot(Protocol::STATUS, StatusAnswerSingleton::getInstance());
    proto->registerSlot(Protocol::REQUEST_STATUS, RequestStatusAnswerSingleton::getInstance());
    proto->registerSlot(Protocol::CONNECT_TO_ME, ConnectToMe::getInstance());
    proto->registerSlot(Protocol::CALL, CallAnswerSingleton::getInstance());
    proto->registerSlot(Protocol::TEXT, TextMessageAnswerSingleton::getInstance());
    proto->registerSlot(Protocol::HANGUP, HangUpAnswerSingleton::getInstance());

    std::cout << "Connecting {{---}}" << std::endl;
    if (!_net->getSocket()->connect("10.18.207.171", 4646))
        _connection = false;
    else
        _connection = true;

    Protocol::getInstance()->defaultGateway(_net);
    PortableNetworkManagerSingle::getInstance()->addNetwork(_net);

    AudioThreadSingleton::getInstance()->start();

    connect(MainWindowSingleton::getInstance(), SIGNAL(closeConnection(QString const &,QString const &)), this, SLOT(disconnectClient(QString const &, QString const &)));
    connect(DockWidgetContentSingleton::getInstance(), SIGNAL(newClient(QString const &)), this, SLOT(addNewClient(QString const &)));
    connect(DockWidgetContentSingleton::getInstance(), SIGNAL(clientStatus(int, QList<std::string> const &)), this, SLOT(updateClientStatus(int, QList<std::string> const &)));
    connect(AccountSingleton::getInstance(), SIGNAL(accountCreation(QString const&,QString const&)), this, SLOT(createAccount(QString const&, QString const&)));
    connect(CentralWidgetSingleton::getInstance(), SIGNAL(newLink(QString const &)), this, SLOT(createNewLink(QString const &)));
    connect(CentralWidgetSingleton::getInstance(), SIGNAL(needOpenTalkWindow(QString)), this, SLOT(openTalkWindow(QString)));
    connect(CentralWidgetSingleton::getInstance(), SIGNAL(textChanged(QString const &,QString const &)), this, SLOT(sendText(QString const &, QString const &)));
    connect(CentralWidgetSingleton::getInstance(), SIGNAL(hangUpTalk(QString const &,QString const &)), this, SLOT(hangUp(QString const &, QString const &)));
}

void    ListenServer::emitHungUp(std::string const &contactLogin)
{
    emit hungUp(QString(contactLogin.c_str()));
}

void    ListenServer::hangUp(QString const &senderLogin, QString const &contactLogin)
{
    HangUpSingleton::getInstance()->sendHangUp(senderLogin.toStdString(), contactLogin.toStdString());
    AudioThreadSingleton::getInstance()->quit();


}

void    ListenServer::emitTextMessageChanged(const std::string &text)
{
    emit textMessageChanged(QString(text.c_str()));
}

void    ListenServer::sendText(QString const &login, QString const &text)
{
    TextMessageSingleton::getInstance()->sendTextMessage(login.toStdString(), text.toStdString());
}

void    ListenServer::emitAddContactToUpdateList(const std::string &login)
{
    emit newContactToUpdateList(QString(login.c_str()));
}

void    ListenServer::disconnectClient(QString const &login, QString const &password)
{
    Q_UNUSED(login);
    Q_UNUSED(password);

    _net->getSocket()->disconnect();
}

void    ListenServer::emitCallFail()
{
    emit callFail();
}

void    ListenServer::emitCall(std::string const &login, unsigned int id)
{
    emit callOccured(QString(login.c_str()), id);
    std::cout << "CALLING THE MOON" << std::endl;
}

void    ListenServer::createAccount(QString const &login, QString const &password)
{
    ConnectionLoginSingleton::getInstance()->registerAccount(login.toStdString(), password.toStdString());
}

void    ListenServer::emitContactStatusChanged(std::string const &login, int status)
{
    emit contactStatusChanged(QString(login.c_str()), status);
}


void ListenServer::openTalkWindow(const QString &login)
{
    CentralWidgetSingleton::getInstance()->addTalkWindow(login);
}

void    ListenServer::updateClientStatus(int status, QList<std::string> const &contactUpdateList)
{
    StatusSingleton::getInstance()->updateStatus(status, contactUpdateList.toStdList());
}

void    ListenServer::addNewClient(QString const &login)
{
    StatusSingleton::getInstance()->requestStatus(login.toStdString());
}

void    ListenServer::createNewLink(QString const &login)
{
    std::cout << "CREATE NEW LINK" << std::endl;
    RequestLinkSingleton::getInstance()->createNewLink(login.toStdString());

    if (!AudioThreadSingleton::getInstance()->isRunning())
        AudioThreadSingleton::getInstance()->start();
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
        PortableNetworkManagerSingle::getInstance()->run(TimerPoolSingleton::getInstance()->getMsNextCall());
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
    //AudioThreadSingleton::getInstance()->addLogin("lol");
    std::cout << "C'est bon !!" << std::endl;
    emit connected();
}

ListenServer::~ListenServer()
{

}

