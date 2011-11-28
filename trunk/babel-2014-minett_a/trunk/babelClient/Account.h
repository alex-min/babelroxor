#ifndef Account_H
#define Account_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CustomButton.h"
#include "RegisterAccount.h"
#include "InterfaceAccount.h"
#include "singleton.h"

namespace Graphic
{
class Account : public QWidget, public InterfaceAccount
{
    Q_OBJECT

public:
    Account();
    virtual void    createAccount(std::string login, std::string password);
    virtual void    logInAccount();
    ~Account();

public slots:
    void    createFormAccount(QString);
    void    validFormAccount(int status);
    void    logIn();

private:
    QGroupBox   _box;
    QFormLayout _boxLayout;
    QVBoxLayout _layout;
    QLabel      _login;
    QLabel      _password;
    QLineEdit    _loginLineEdit;
    QLineEdit    _passwordLineEdit;
    QLabel      _info;
    QLabel      _createAccount;
    QPushButton _connectionButton;
};
}

typedef Singleton<Graphic::Account>  AccountSingleton;

#endif // Account_H
