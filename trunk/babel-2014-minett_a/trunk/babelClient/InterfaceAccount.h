#ifndef INTERFACEACCOUNT_H
#define INTERFACEACCOUNT_H

#include <iostream>

namespace Graphic
{
class InterfaceAccount
{
public:
    virtual void    createAccount(std::string login, std::string password) = 0;
    virtual void    logInAccount() = 0;
};
}
#endif // INTERFACEACCOUNT_H
