#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include <map>
#include "network.h"
#include "networkroute.h"

class AccountManager
{
private:
    AccountManager();
public:
    static AccountManager *getInstance();
    void setLoginToNetwork(Network *network, std::string const &login);
    std::string const &getLoginFromNetwork(Network *network);
    Network *getNetworkFromLogin(std::string const &login) const;
    Network *getNetworkFromLogin(const void *data, const unsigned int length) const;
    static std::string dataTologin(const void *data, const unsigned int len);

private:
    static AccountManager *_instance;
    std::map<Network *, std::string> _mapLogin;
};

#endif // ACCOUNTMANAGER_H
