#ifndef QTPOPUPMESSAGE_H
#define QTPOPUPMESSAGE_H

#include <QObject>
#include <QMessageBox>
#include <QIcon>
#include "InterfacePopupMessage.h"

namespace Graphic
{
class   QtPopUpMessage : public QMessageBox, public InterfacePopupMessage
{
    Q_OBJECT

public:

    struct AssocIcon
    {
        QtPopUpMessage::PopUpType type;
        QMessageBox::Icon ico;
    };

    virtual void    setTitle(std::string const &title);
    virtual std::string const&    getTitle();
    virtual void    setText(std::string const &text);
    virtual std::string const&    getText();
    virtual void    setIcon(std::string const &icon);
    virtual std::string const&    getIcon();
    virtual void   setType(PopUpType type);
    virtual QtPopUpMessage::PopUpType   getType() const;
    virtual void   setButtonType(int buttonType);
    virtual int getButtonType() const;
    virtual std::string const &getLogin();
    virtual void               setLogin(std::string const &login);
    static QtPopUpMessage*  createPopUp(QtPopUpMessage::PopUpType type, std::string const &title, std::string const &text, std::string const &icon = "");

private:
    QtPopUpMessage(std::string const &title, std::string const &text, QMessageBox::Icon icon = QMessageBox::NoIcon);

private:
    static PopUpType   _type;
    static std::string _title;
    static std::string _text;
    static std::string _icon;
    static std::string _login;
    static AssocIcon   _assocTab[5];
    static ButtonType  _buttonType;
};
}

#endif // QTPOPUPMESSAGE_H
