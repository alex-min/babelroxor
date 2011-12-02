#include "QtPopupMessage.h"
#include <QDebug>

namespace Graphic
{
QtPopUpMessage::PopUpType QtPopUpMessage::_type = QtPopUpMessage::NOTYPE;
std::string QtPopUpMessage::_title = "";
std::string QtPopUpMessage::_text = "";
std::string QtPopUpMessage::_icon = "";
std::string QtPopUpMessage::_login = "";
QtPopUpMessage::ButtonType  QtPopUpMessage::_buttonType = QtPopUpMessage::BaseButton;

QtPopUpMessage::AssocIcon QtPopUpMessage::_assocTab[] =
{
    {QtPopUpMessage::ERR, QMessageBox::Critical},
    {QtPopUpMessage::INFORMATION, QMessageBox::Information},
    {QtPopUpMessage::NOTYPE, QMessageBox::NoIcon},
    {QtPopUpMessage::WARNING, QMessageBox::Warning},
    {(QtPopUpMessage::PopUpType)(0), QMessageBox::Icon(0)}
};

QtPopUpMessage::QtPopUpMessage(std::string const &title, std::string const &text, QMessageBox::Icon icon)
    : QMessageBox(icon, QString(title.c_str()), QString(text.c_str()))
{
    _title = title;
    _text = text;

    setWindowModality(Qt::ApplicationModal);
}

std::string const &QtPopUpMessage::getLogin()
{
    return (_login);
}

void        QtPopUpMessage::setLogin(std::string const &login)
{
    _login = login;
}

QtPopUpMessage*  QtPopUpMessage::createPopUp(QtPopUpMessage::PopUpType type, std::string const &title, std::string const &text, std::string const &icon)
{
    QtPopUpMessage *popUp = 0;
    QMessageBox::Icon   ico = QMessageBox::NoIcon;

    for (int i = 0; _assocTab[i].type; i++)
        if (_assocTab[i].type == type)
        {
            ico = _assocTab[i].ico;
            break;
        }

    popUp = new QtPopUpMessage(title, text, ico);

    if (!icon.empty())
    {
        popUp->setIconPixmap(QPixmap(icon.c_str()));
        popUp->setIcon(icon);
    }

    return (popUp);
}

void    QtPopUpMessage::setTitle(std::string const &title)
{
    _title = title;
}


std::string const&    QtPopUpMessage::getTitle()
{
    return (_title);
}


void    QtPopUpMessage::setText(std::string const &text)
{
    _text = text;
}


std::string const&    QtPopUpMessage::getText()
{
    return (_text);
}


void    QtPopUpMessage::setIcon(std::string const &icon)
{
    _icon = icon;
}


std::string const&    QtPopUpMessage::getIcon()
{
    return (_icon);
}


QtPopUpMessage::PopUpType   QtPopUpMessage::getType() const
{
    return (_type);
}


void   QtPopUpMessage::setType(PopUpType type)
{
    _type = type;
}

int   QtPopUpMessage::getButtonType() const
{
    return (_buttonType);
}

void    QtPopUpMessage::setButtonType(int buttonType)
{
    bool acceptButton = false;
    bool refuseButton = false;
    StandardButtons buttons = QMessageBox::NoButton;

    if (buttonType & QtPopUpMessage::AcceptButton)
    {
        acceptButton = true;
        buttons |= QMessageBox::Yes;
    }
    if (buttonType & QtPopUpMessage::RefuseButton)
    {
        refuseButton = true;
        buttons |= QMessageBox::No;
    }

    setStandardButtons(buttons);
}
}
