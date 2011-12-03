#ifndef INTERFACEACCOUNT_H
#define INTERFACEACCOUNT_H

#include <iostream>

namespace Graphic
{
class InterfaceAccount
{
public:
    virtual void    createAccount(std::string login, std::string password) = 0;
    virtual void    logInAccount(std::string const &login, std::string const &password) = 0;
    virtual std::string const &getLogin() = 0;
    virtual std::string const &getPassword() = 0;


};
}
#endif // INTERFACEACCOUNT_H
