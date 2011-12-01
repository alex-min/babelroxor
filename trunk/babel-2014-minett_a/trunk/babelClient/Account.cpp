#include "Account.h"
#include <QDebug>

namespace Graphic
{
Account::Account()
{
    _connectLogin = "";
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

void    Account::logInAccount(std::string const &login, std::string const &password)
{
    ConnectionLoginSingleton::getInstance()->connect(login, password);
}

std::string const &Account::getLogin()
{
    _connectLogin = _loginLineEdit.text().toStdString();

    return (_connectLogin);
}

void    Account::resetFields()
{
    _loginLineEdit.clear();
    _passwordLineEdit.clear();
    _connectLogin = "";
}

void    Account::logIn()
{
    std::string login = _loginLineEdit.text().toStdString();
    std::string password = _passwordLineEdit.text().toStdString();

    if (login != "" && password != "")
        logInAccount(login, password);
    else
    {
        QtPopUpMessage *popUp = QtPopUpMessage::createPopUp(QtPopUpMessage::WARNING, "Warning", "You must fill all the fields to connect you to an account");

        popUp->setIconPixmap(QPixmap("../trunk/images/warning.png"));
        popUp->show();

        connect(popUp, SIGNAL(finished(int)), popUp, SLOT(deleteLater()));
    }
}

void    Account::createAccount(std::string login, std::string password)
{
    emit accountCreation(QString(login.c_str()), QString(password.c_str()));
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
