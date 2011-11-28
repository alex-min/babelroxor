#ifndef INTERFACEREGISTERACCOUNT_H
#define INTERFACEREGISTERACCOUNT_H

namespace Graphic
{
class InterfaceRegisterAccount
{
public:
    virtual void    validAccount(int status) = 0;
    virtual std::string const &getLogin() = 0;
    virtual std::string const &getPassword() = 0;
};
}

#endif // INTERFACEREGISTERACCOUNT_H
