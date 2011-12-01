#include <QtGui/QApplication>
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
#include "connecttome.h"
#include "ListenServer.h"
#include "MainWindow.h"
#include "portaudio.h"

#ifdef OS_WINDOWS
#define start_entry qMain
#else
#define start_entry main
#endif

int main(int ac, char **av)
{

    QApplication app(ac, av);
    Graphic::MainWindow *win = MainWindowSingleton::getInstance();
  //  RequestLinkSingleton::getInstance();
    ListenServerSingleton::getInstance()->start();

    win->init();

    QFile fileStyle("../trunk/css/babelStyle.css");

    if (fileStyle.open(QIODevice::ReadOnly))
    {
        app.setStyleSheet(fileStyle.readAll());
        fileStyle.close();
    }

    win->show();

    return (app.exec());

    //    return (0);
    //        Network *net = new Network;
    // Protocol *proto = Protocol::getInstance();
    // ConnectionSlot *c = new ConnectionSlot;
    // ProxySlot *p = new ProxySlot;
    // proto->registerSlot(Protocol::AUDIO, AudioSlotSingle::getInstance());
    // proto->registerSlot(Protocol::CONNECTION, ProtocolInterfaceSlot::getInstance());
    // proto->registerSlot(Protocol::PROXY_FORWARD, p);
    // proto->registerSlot(Protocol::TEST_CONNECTION, TestConnectionSingleton::getInstance());
    // proto->registerSlot(Protocol::CONNECT_TO_ME, ConnectToMe::getInstance());
    // proto->registerSlot(Protocol::PROXY_RECEIVED, ProxyReceivedSlotSingleton::getInstance());


    // PortableNetworkManager *m = PortableNetworkManagerSingle::getInstance();

    //   if (!net->getSocket()->connect("127.0.0.1", 4646))
    //       return (0);

    //    Protocol::getInstance()->defaultGateway(net);
    //    m->addNetwork(net);
    //    ConnectionLoginSingle::getInstance()->connect(av[1], "plop");
    //    std::cout << ac << std::endl;
    //    if (ac == 4 && atoi(av[2]) == 1)
    //    {
    //        std::cout << "Requesting link" << std::endl;
    //        RequestLinkSingleton::getInstance()->createNewLink(av[3]);
    //    }


    //while (1)
    //{
    //    m->run(TimerPoolSingleton::getInstance()->getMsNextCall());
    //    TimerPoolSingleton::getInstance()->autocall();
    //}
    //    std::cout << "Exiting" << std::endl;
    //    return (0);
}
