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
#include "connectionlogin.h"

#ifdef OS_UNIX
#define MAIN    main
#else
#define MAIN    qMain
#endif

int	MAIN(int ac, char **av)
{
    PortableTime pr;

//    while (1) {
  //   pr.setToMsTimeOfDay();

    //}
    PortableTime *test = new PortableTime();
    test->setToMsTimeOfDay();

    //    std::cout << "ok" << std::endl;
    Network *net = new Network;
    //    std::cout << "ok" << std::endl;
    Protocol *proto = Protocol::getInstance();
    // std::cout << "ok" << std::endl;
     ProxySlot *p = new ProxySlot;
    // std::cout << "ok" << std::endl;
    proto->registerSlot(Protocol::CONNECTION, ConnectionLoginSlot::getInstance());
    // std::cout << "ok" << std::endl;
    proto->registerSlot(Protocol::PROXY_FORWARD, p);
    // std::cout << "ok" << std::endl;
    proto->registerSlot(Protocol::TEST_CONNECTION, TestConnectionSingleton::getInstance());
    // std::cout << "ok" << std::endl;
    proto->registerSlot(Protocol::PROXY_RECEIVED, ProxyReceivedSlotSingleton::getInstance());
    // std::cout << "ok" << std::endl;

    PortableNetworkManager m;

    std::cout << "ok" << std::endl;

    if (!net->getSocket()->createServerSocket(IPortableSocket::TCP, 4646))
    {
        std::cout << "ok" << std::endl;
        return (0);
    }
    m.addNetwork(net);
    std::cout << "Starting server [OK]" << std::endl;

    while (1)
    {
        m.run(TimerPoolSingleton::getInstance()->getMsNextCall());
        TimerPoolSingleton::getInstance()->autocall();
    }
    std::cout << "Exiting" << std::endl;
    return (0);
}
