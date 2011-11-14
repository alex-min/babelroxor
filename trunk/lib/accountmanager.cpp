#include "accountmanager.h"

AccountManager *AccountManager::_instance = NULL;

AccountManager::AccountManager()
{
    _mapLogin[NULL] = "";
}

AccountManager *AccountManager::getInstance()
{
    if (_instance == NULL)
        _instance = new AccountManager;
    return (_instance);
}

bool    AccountManager::checkIfAccountExist(std::string const &login) const
{
    std::list<Account*>::const_iterator it;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if ((*it)->getLogin() == login)
            return (true);

    return (false);
}

bool   AccountManager::createAccount(std::string const &login, std::string const &password)
{
    if (checkIfAccountExist(login))
        return (false);

    Account *account = new Account(login, password);

    _accountList.push_back(account);

    return (true);
}

Account const*    AccountManager::getAccountAt(int id) const
{
    std::list<Account*>::const_iterator it;
    int i = 0;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if (i++ == id)
            return (*it);

    return (0);
}


Account*    AccountManager::getAccountAt(int id)
{
    std::list<Account*>::iterator it;
    int i = 0;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if (i++ == id)
            return (*it);

    return (0);
}

Account const*  AccountManager::getAccountFromLogin(std::string const &login) const
{
    std::list<Account*>::const_iterator it;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if ((*it)->getLogin() == login)
            return (*it);

    return (0);
}

Account*    AccountManager::getAccountFromLogin(std::string const &login)
{
    std::list<Account*>::iterator it;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if ((*it)->getLogin() == login)
            return (*it);

    return (0);
}

bool    AccountManager::removeAccount(Account* account)
{
    std::list<Account*>::iterator it;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if (*it == account)
        {
            it = _accountList.erase(it);
            delete account;

            return (true);
        }

    return (false);
}

bool    AccountManager::removeAccountFromLogin(std::string const &login)
{
    std::list<Account*>::iterator it;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if ((*it)->getLogin() == login)
        {
            Account *account = *it;

            it = _accountList.erase(it);
            delete account;

            return (true);
        }

    return (false);
}

bool    AccountManager::removeAccountAt(int id)
{
    std::list<Account*>::iterator it;
    int i = 0;

    for (it = _accountList.begin(); it != _accountList.end(); ++it)
        if (i++ == id)
        {
            Account *account = *it;

            it = _accountList.erase(it);
            delete account;

            return (true);
        }

    return (false);
}


void AccountManager::setLoginToNetwork(Network *network, std::string const &login)
{
     _mapLogin[network] = login;
}

std::string const &AccountManager::getLoginFromNetwork(Network *network)
{
    if (_mapLogin.find(network) != _mapLogin.end())
         return (_mapLogin[network]);
    return (_mapLogin[NULL]);
}

Network *AccountManager::getNetworkFromLogin(const void *data, const unsigned int length) const
{
    bool nullTerminated = false;

    for (unsigned int i = 0; i < length; ++i)
    {
        if (static_cast<const char *>(data)[i] == 0)
           nullTerminated = true;
    }
    if (!nullTerminated || static_cast<const char *>(data)[0] == 0) // empty login or invalid logins are forbiden
        return (NULL);
    return (AccountManager::getNetworkFromLogin(std::string(static_cast<const char *>(data))));
}

Network *AccountManager::getNetworkFromLogin(std::string const &login) const
{
    for (std::map<Network *, std::string>::const_iterator it = _mapLogin.begin(); it != _mapLogin.end(); ++it)
    {
        if (it->second == login)
            return (it->first);
    }
    return (NULL);
}

std::string AccountManager::dataTologin(const void *data, const unsigned int len)
{
    bool nullTerminated = false;

    for (unsigned int i = 0; i < len; ++i)
    {
        if (static_cast<const char *>(data)[i] == 0)
           nullTerminated = true;
    }
    if (!nullTerminated || static_cast<const char *>(data)[0] == 0) // empty login or invalid logins are forbiden
        return (std::string());
    return (std::string(static_cast<const char *> (data)));
}
