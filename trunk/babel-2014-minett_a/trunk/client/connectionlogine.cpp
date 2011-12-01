#include "connectionlogine.h"

ConnectionLogin::ConnectionLogin()
{
}

void ConnectionLogin::connect(const std::string &login, const std::string &password)
{
    if (login == "" || password == "")
        return ;
    short unsigned int id = Protocol::getInstance()->getCurrentReplyId();

    Protocol::getInstance()->send("", Protocol::CONNECTION, std::string(login + std::string("\0", 1) + password).c_str(),
                   login.length() + password.length() + 1, id, false);
    Protocol::getInstance()->registerPacketId(id, login, Protocol::getInstance()->getDefaultGetaway(),
                                              ProtocolInterfaceSlot::getInstance(),
                                              reinterpret_cast<Protocol::SlotCall> (&_ProtocolInterfaceSlot::loginSlot),
                                              Protocol::DEFAULT_TIMEOUT);
}

void    ConnectionLogin::registerAccount(std::string const &login, std::string const &password)
{
    if (login == "" || password == "")
        return ;

    std::cout << "REQUEST TO REGISTER AN ACCOUNT" << std::endl;

    short unsigned int id = Protocol::getInstance()->getCurrentReplyId();

    Protocol::getInstance()->send("", Protocol::REGISTER, std::string(login + std::string("\0", 1) + password).c_str(),
                   login.length() + password.length() + 1, id, false);

    Protocol::getInstance()->registerPacketId(id, login, Protocol::getInstance()->getDefaultGetaway(),
                                              ProtocolInterfaceSlot::getInstance(),
                                              reinterpret_cast<Protocol::SlotCall> (&_ProtocolInterfaceSlot::registerSlot),
                                              Protocol::DEFAULT_TIMEOUT);
}
