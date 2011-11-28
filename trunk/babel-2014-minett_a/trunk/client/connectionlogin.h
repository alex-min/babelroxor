#ifndef CONNECTIONLOGINE___H
#define CONNECTIONLOGINE___H
#include <string>
#include "protocol.h"
#include "singleton.h"
#include "islotinterface.h"
#include "protocolinterfaceslot.h"

class ConnectionLogin
{
public:
    ConnectionLogin();
    void connect(std::string const &login,
                 std::string const &password);
    void    registerAccount(std::string const &login,
                             std::string const &password);
};

typedef Singleton<ConnectionLogin> ConnectionLoginSingleton;

#endif // CONNECTIONLOGIN_H
