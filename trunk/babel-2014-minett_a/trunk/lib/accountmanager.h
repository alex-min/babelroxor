#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include <map>
#include <list>

#include "network.h"
#include "networkroute.h"
#include "account.h"

class AccountManager
{
private:
    AccountManager();
public:
    static AccountManager *getInstance();
    void setLoginToNetwork(Network *network, std::string const &login);
    void removeNetwork(Network *net);
    std::string const &getLoginFromNetwork(Network *network);
    Network *getNetworkFromLogin(std::string const &login) const;
    Network *getNetworkFromLogin(const void *data, const unsigned int length) const;
    static std::string dataTologin(const void *data, const unsigned int len);
    bool    checkIfAccountExist(std::string const &login) const;
    bool    createAccount(std::string const &login, std::string const &password);
    Account const*      getAccountAt(int id) const;
    Account*            getAccountAt(int id);
    Account const*      getAccountFromLogin(std::string const &login) const;
    Account*            getAccountFromLogin(std::string const &login);
    bool                removeAccount(Account* account);
    bool                removeAccountFromLogin(std::string const &login);
    bool                removeAccountAt(int id);

private:
    static AccountManager *_instance;
    std::map<Network *, std::string> _mapLogin;
    std::list<Account*>     _accountList;
};

#endif // ACCOUNTMANAGER_H
