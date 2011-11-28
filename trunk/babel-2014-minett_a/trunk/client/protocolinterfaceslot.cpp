#include "protocolinterfaceslot.h"
#include "requestlink.h"
#include "MainWindow.h"

_ProtocolInterfaceSlot::_ProtocolInterfaceSlot()
{
}

void _ProtocolInterfaceSlot::loginSlot(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        Graphic::QtPopUpMessage *popup = Graphic::QtPopUpMessage::createPopUp(Graphic::QtPopUpMessage::WARNING,
                                                                              "Log-in", "Your login or password is wrong.");

        QObject::connect(popup, SIGNAL(finished(int)), popup, SLOT(deleteLater()));

        std::cerr << "[err] Cannot login to host : " << timeout << std::endl;
        return ;
    }
    std::cout << "[ok] Connection success to server" << std::endl;
    RequestLinkSingleton::getInstance()->createNewLink("oo");
    MainWindowSingleton::getInstance()->switchOnConnectedState();
}

void _ProtocolInterfaceSlot::registerSlot(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        Graphic::QtPopUpMessage *popup = Graphic::QtPopUpMessage::createPopUp(Graphic::QtPopUpMessage::WARNING,
                                                                              "Validation account", "Your account cannot be created.");

        QObject::connect(popup, SIGNAL(finished(int)), popup, SLOT(deleteLater()));

        std::cerr << "[err] Cannot login to host : " << timeout << std::endl;
        return ;
    }

    std::cout << "[ok] Register success" << std::endl;

    Graphic::QtPopUpMessage *popup = Graphic::QtPopUpMessage::createPopUp(Graphic::QtPopUpMessage::INFORMATION,
                                                                          "Validation account", "Your account is successfully created.");

    QObject::connect(popup, SIGNAL(finished(int)), popup, SLOT(deleteLater()));
}
