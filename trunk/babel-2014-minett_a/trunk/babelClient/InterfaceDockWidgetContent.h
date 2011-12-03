#ifndef INTERFACEDOCKWIDGETCONTENT_H
#define INTERFACEDOCKWIDGETCONTENT_H

namespace Graphic
{
class InterfaceDockWidgetContent
{
public:
    virtual std::string const &    getCurrentContactLogin() = 0;
    virtual std::string const &    getLogin() = 0;
    virtual void                   setLogin(std::string const &login) = 0;
    virtual void    showCallPopUp() = 0;
    virtual void    updateClientAvatar(std::string const &filename) = 0;
    virtual void    updateContactStatus(std::string const &login, int status) = 0;
    virtual void    addClientContact(std::string const &login) = 0;
    virtual void    removeCurrentClientContact(std::string const &login) = 0;
};
}

#endif // INTERFACEDOCKWIDGETCONTENT_H
