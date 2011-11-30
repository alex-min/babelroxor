#include "ListenServer.h"
#include "audiothread.h"
#include <QCoreApplication>

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
    Protocol::getInstance()->registerSlot(Protocol::STATUS, StatusAnswerSingleton::getInstance());
    //    Protocol::getInstance()->registerSlot(Protocol::CALL, CallAnswerSingleton::getInstance());

    std::cout << "Connecting {{---}}" << std::endl;
    if (!net->getSocket()->connect("10.18.207.136", 4646))
        _connection = false;
    else
        _connection = true;

    Protocol::getInstance()->defaultGateway(net);
    _networkManager.addNetwork(net);
}

void    ListenServer::run(void)
{
    //    AudioThread t;
    //  t.start();
    if (!_connection)
        return;

    AudioThreadSingleton::getInstance()->start();
    while (1)
    {
        QCoreApplication::processEvents();
        _networkManager.run(TimerPoolSingleton::getInstance()->getMsNextCall());
        TimerPoolSingleton::getInstance()->autocall();
    }

    std::cout << "Exiting" << std::endl;
}
void    ListenServer::emitConnectionPopUpWarning(std::string const &title, std::string const &text)
{
    std::cout << "Rintintin" << std::endl;
    emit connectionPopUpWarning(QString(title.c_str()), QString(text.c_str()));
}

void    ListenServer::emitConnected()
{
    std::cout << "C'est bon !!" << std::endl;
    AudioThreadSingleton::getInstance()->addLogin("lol");
    emit connected();
}

ListenServer::~ListenServer()
{

}
