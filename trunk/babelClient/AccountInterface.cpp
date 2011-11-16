#include "AccountInterface.h"
#include <QDebug>

AccountInterface::AccountInterface(QWidget *parent)
    : QWidget(parent)
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

    connect(&_createAccount, SIGNAL(linkActivated(QString)), this, SLOT(createAccount(QString)));
    connect(&_connectionButton, SIGNAL(clicked()), this, SLOT(logInAccount()));
}

void    AccountInterface::logInAccount()
{
    //send a request to the server to logIn the account
}

void    AccountInterface::createAccount(QString)
{
    RegisterAccountInterface    *registerAccount = new RegisterAccountInterface;

    connect(registerAccount, SIGNAL(finished(int)), registerAccount, SLOT(deleteLater()));
}

AccountInterface::~AccountInterface()
{

}
