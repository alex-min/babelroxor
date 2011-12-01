#include "RegisterAccount.h"
#include <QDebug>

namespace Graphic
{
RegisterAccount::RegisterAccount(QWidget *parent)
    : QDialog(parent)
{
    _login = "";
    _password = "";

    _valid.setShape(CustomButton::ROUND);
    _valid.setText("Ok");

    _cancel.setShape(CustomButton::ROUND);
    _cancel.setText("Cancel");

    _text.setText("Fill the login and password field before click on the valid button\nto create your account.");
    _text.setObjectName("registerTextInfo");
    _loginLabel.setText("Login :");
    _loginLabel.setObjectName("registerLogin");
    _passwordLabel.setText("Password :");
    _passwordLabel.setObjectName("registerPassword");

    _passwordLineEdit.setEchoMode(QLineEdit::Password);
    _valid.setRadius(8.0, 8.0);
    _valid.setBold(true);
    _cancel.setRadius(8.0, 8.0);
    _cancel.setBold(true);

    _hl1.addWidget(&_loginLabel);
    _hl1.addWidget(&_loginLineEdit);
    _hl1.setSpacing(30);

    _hl2.addWidget(&_passwordLabel);
    _hl2.addWidget(&_passwordLineEdit);

    _hl3.addWidget(&_valid);
    _hl3.addWidget(&_cancel);

    _layout.addWidget(&_text, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignTop);
    _layout.addLayout(&_hl1, 1, 0, 1, 1, Qt::AlignTop);
    _layout.addLayout(&_hl2, 2, 0, 1, 1, Qt::AlignTop);
    _layout.addLayout(&_hl3, 3, 0, 1, 1);

    setLayout(&_layout);

    setWindowTitle("Register account");
    setWindowModality(Qt::ApplicationModal);

    setFixedSize(550, 400);
    setObjectName("createAccount");
    show();

    connect(&_valid, SIGNAL(clicked()), this, SLOT(checkStatus()));
    connect(&_cancel, SIGNAL(clicked()), this, SLOT(checkStatus()));
}

std::string const&  RegisterAccount::getLogin()
{
    _login = _loginLineEdit.text().toStdString();

    return (_login);
}

std::string const&  RegisterAccount::getPassword()
{
    _password = _passwordLineEdit.text().toStdString();

    return (_password);
}

void    RegisterAccount::checkStatus()
{
    CustomButton *button = qobject_cast<CustomButton*>(sender());

    if (button->text() == "Ok")
        validAccount(1);
    else
        validAccount(0);
}

void    RegisterAccount::validAccount(int status)
{
    if (status == 1)
    {
        std::string login = _loginLineEdit.text().toStdString();
        std::string password = _passwordLineEdit.text().toStdString();

        if (login == "" || password == "")
        {
            QtPopUpMessage *popUp = QtPopUpMessage::createPopUp(QtPopUpMessage::WARNING, "Warning", "You must fill all the fields to create an account");

            popUp->setIconPixmap(QPixmap("../trunk/images/warning.png"));
            popUp->show();
        }
        else
            accept();
    }
    else
        close();

}

RegisterAccount::~RegisterAccount()
{

}
}
