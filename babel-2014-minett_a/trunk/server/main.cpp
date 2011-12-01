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
#include "registeraccount.h"

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

    Network *net = new Network;
    Protocol *proto = Protocol::getInstance();
    ProxySlot *p = new ProxySlot;

    proto->registerSlot(Protocol::CONNECTION, ConnectionLoginSlot::getInstance());
    proto->registerSlot(Protocol::REGISTER, RegisterAccountSingleton::getInstance());
    proto->registerSlot(Protocol::PROXY_FORWARD, p);
    proto->registerSlot(Protocol::TEST_CONNECTION, TestConnectionSingleton::getInstance());
    proto->registerSlot(Protocol::PROXY_RECEIVED, ProxyReceivedSlotSingleton::getInstance());

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
