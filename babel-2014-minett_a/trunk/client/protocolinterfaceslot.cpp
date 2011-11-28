#include "protocolinterfaceslot.h"
#include "requestlink.h"

_ProtocolInterfaceSlot::_ProtocolInterfaceSlot()
{
}

void _ProtocolInterfaceSlot::loginSlot(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        // throw popup
        std::cerr << "[err] Cannot login to host : " << timeout << std::endl;
        return ;
    }
    std::cout << "[ok] Connection success to server" << std::endl;
    RequestLinkSingleton::getInstance()->createNewLink("oo");
}

void _ProtocolInterfaceSlot::registerSlot(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        // throw popup
        std::cerr << "[err] Cannot login to host : " << timeout << std::endl;
        return ;
    }
    std::cout << "[ok] Register success" << std::endl;

    Graphic::QtPopUpMessage *popup = Graphic::QtPopUpMessage::createPopUp(Graphic::QtPopUpMessage::INFORMATION,
                                                                          "Confirmation de la creation d'un compte", "Votre compte a bien ete creer");

    QObject::connect(popup, SIGNAL(finished(int)), popup, SLOT(deleteLater()));
}
