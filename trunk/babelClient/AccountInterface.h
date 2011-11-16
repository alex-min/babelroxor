#ifndef ACCOUNTINTERFACE_H
#define ACCOUNTINTERFACE_H

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
#include "RegisterAccountInterface.h"

class AccountInterface : public QWidget
{
    Q_OBJECT

public:
    AccountInterface(QWidget *parent = 0);
    ~AccountInterface();

public slots:
    void    createAccount(QString);
    void    logInAccount();

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

#endif // ACCOUNTINTERFACE_H
