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

#include "My_Speex.h"
#include "AudioCallback.h"
#include "AudioHandler.h"
#include "DecoderSpeex.h"
#include "EncoderSpeex.h"

#ifdef OS_WINDOWS
#define start_entry qMain
#else
#define start_entry main
#endif

int main(int ac, char **av)
{
    QApplication app(ac, av);
    Graphic::MainWindow *win = MainWindowSingleton::getInstance();

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
}
