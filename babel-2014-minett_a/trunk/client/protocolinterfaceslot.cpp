#include "protocolinterfaceslot.h"
#include "requestlink.h"
#include "MainWindow.h"
#include "ListenServer.h"

_ProtocolInterfaceSlot::_ProtocolInterfaceSlot()
{
}

void _ProtocolInterfaceSlot::loginSlot(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        ListenServerSingleton::getInstance()->emitWarningPopUp("Log-in", "Either you have not created an account with these fields "
                                                               "or you are already connected to this account.");

        std::cerr << "[err] Cannot login to host : " << timeout << std::endl;
        return ;
    }

    std::cout << "[ok] Connection success to server" << std::endl;

    ListenServerSingleton::getInstance()->emitConnected();
}

void _ProtocolInterfaceSlot::registerSlot(bool timeout, Packet *p)
{
    if (timeout || !p || p->getStatus() == Protocol::FAILED)
    {
        ListenServerSingleton::getInstance()->emitWarningPopUp("Validation account", "This account already exist.");

        std::cerr << "[err] Cannot register account to host : " << timeout << std::endl;
        return ;
    }

    std::cout << "[ok] Register success" << std::endl;

    ListenServerSingleton::getInstance()->emitSuccessPopUp("Validation account", "Your account is successfully created.");
}
