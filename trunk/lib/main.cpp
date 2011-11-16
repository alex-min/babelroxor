#include <QtGui/QApplication>
#include "mainwindow.h"
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

int main(void)
{

    Network *server = new Network;
 Protocol *proto = Protocol::getInstance();
 Audio *a = new Audio;
 ConnectionSlot *c = new ConnectionSlot;
 ProxySlot *p = new ProxySlot;
 proto->registerSlot(Protocol::AUDIO, a);
 proto->registerSlot(Protocol::CONNECTION, c);
 proto->registerSlot(Protocol::PROXY_FORWARD, p);
 std::cout << Protocol::TEST_CONNECTION << std::endl;
 proto->registerSlot(Protocol::TEST_CONNECTION, TestConnectionSingleton::getInstance());
 proto->registerSlot(Protocol::PROXY_RECEIVED, ProxyReceivedSlotSingleton::getInstance());

 PortableNetworkManager m;

    RequestLinkSingleton::getInstance()->createServerSock("fff");


m.setProtocol(proto);
if (!(server->getSocket()->createServerSocket(IPortableSocket::TCP, 4575)))
        return (0);
m.addNetwork(server);
while (1)
{
    m.run(TimerPoolSingleton::getInstance()->getMsNextCall());
    TimerPoolSingleton::getInstance()->autocall();
}
    std::cout << "Exiting" << std::endl;
    return (0);
}
