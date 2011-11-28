#include "Account.h"
#include <QDebug>

namespace Graphic
{
Account::Account()
{
    _login.setText("Login :");
    _password.setText("Password :");
    _info.setText("If you have not an account you have to create one :");

    _createAccount.setTextFormat(Qt::RichText);
    _createAccount.setText("<a href=\"...\">Create one here</a>");


    _passwordLineEdit.setEchoMode(QLineEdit::Password);

    _login.setObjectName("loginAccount");
    _loginLineEdit.setObjectName("loginLineEdit");
    _password.setObjectName("passwordAccount");
    _passwordLineEdit.setObjectName("passwordLineEdit");
    _info.setObjectName("info");
    _createAccount.setObjectName("createAccount");
    _box.setObjectName("connectionBox");

    _box.setTitle("Connection");

    _boxLayout.setSpacing(10);

    _boxLayout.addRow(&_login, &_loginLineEdit);
    _boxLayout.addRow(&_password, &_passwordLineEdit);

    _box.setLayout(&_boxLayout);

    _connectionButton.setText("Log-In");
    _connectionButton.setObjectName("connection");

    _layout.addWidget(&_box);
    _layout.addWidget(&_connectionButton);
    _layout.addWidget(&_info);
    _layout.addWidget(&_createAccount);

    _layout.addSpacing(400);

    setLayout(&_layout);

    connect(&_createAccount, SIGNAL(linkActivated(QString)), this, SLOT(createFormAccount(QString)));
    connect(&_connectionButton, SIGNAL(clicked()), this, SLOT(logIn()));
}

void    Account::logInAccount()
{
    //send a request to the server to logIn the account
}

void    Account::logIn()
{
    logInAccount();
}

void    Account::createAccount(std::string login, std::string password)
{
    Q_UNUSED(login);
    Q_UNUSED(password);

    //send a request to the server
}

void    Account::createFormAccount(QString)
{
    RegisterAccount    *registerAccount = new RegisterAccount;

    connect(registerAccount, SIGNAL(finished(int)), this, SLOT(validFormAccount(int)));
}

void    Account::validFormAccount(int status)
{
    RegisterAccount *registerAccount = qobject_cast<RegisterAccount*>(sender());

    if (registerAccount && status == 1)
        createAccount(registerAccount->getLogin(), registerAccount->getPassword());

    registerAccount->deleteLater();
}

Account::~Account()
{

}
}
