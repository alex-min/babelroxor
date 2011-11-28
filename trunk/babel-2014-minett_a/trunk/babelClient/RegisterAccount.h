#ifndef RegisterAccount_H
#define RegisterAccount_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QMessageBox>
#include "CustomButton.h"
#include "InterfaceRegisterAccount.h"
#include "QtPopupMessage.h"

namespace Graphic
{
class RegisterAccount : public QDialog, public InterfaceRegisterAccount
{
    Q_OBJECT

public:
    RegisterAccount(QWidget *parent = 0);
    virtual void    validAccount(int status);
    virtual std::string const &getLogin();
    virtual std::string const &getPassword();
    ~RegisterAccount();

public slots:
    void    checkStatus();

private:
    CustomButton _valid;
    CustomButton _cancel;
    QLabel      _text;
    QLabel      _loginLabel;
    QLineEdit   _loginLineEdit;
    QLabel      _passwordLabel;
    QLineEdit   _passwordLineEdit;
    QGridLayout _layout;
    QHBoxLayout _hl1;
    QHBoxLayout _hl2;
    QHBoxLayout _hl3;
    std::string _login;
    std::string _password;
};
}

#endif // RegisterAccount_H
