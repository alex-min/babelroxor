#ifndef POPUPMESSAGE_H
#define POPUPMESSAGE_H

#include <iostream>

namespace Graphic
{
class InterfacePopupMessage
{
public:
    enum PopUpType { NOTYPE = 1, WARNING, INFORMATION, ERR };
    enum ButtonType { BaseButton = 0x1, AcceptButton = 0x2, RefuseButton = 0x4 };

    virtual void    setTitle(std::string const &title) = 0;
    virtual std::string const&    getTitle() = 0;
    virtual void    setText(std::string const &text) = 0;
    virtual std::string const&    getText() = 0;
    virtual void    setIcon(std::string const &icon) = 0;
    virtual std::string const&    getIcon() = 0;
    virtual PopUpType   getType() const = 0;
    virtual void   setType(PopUpType type) = 0;
    virtual void   setButtonType(int buttonType) = 0;
    virtual int getButtonType() const = 0;
    virtual std::string const &getLogin() = 0;
    virtual void               setLogin(std::string const &login) = 0;

};
}

#endif // POPUPMESSAGE_H
