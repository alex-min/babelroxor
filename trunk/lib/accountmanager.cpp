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
