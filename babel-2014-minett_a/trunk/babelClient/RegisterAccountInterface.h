#ifndef REGISTERACCOUNTINTERFACE_H
#define REGISTERACCOUNTINTERFACE_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QMessageBox>
#include "CustomButton.h"

class RegisterAccountInterface : public QDialog
{
    Q_OBJECT

public:
    RegisterAccountInterface(QWidget *parent = 0);
    void    closeAccountDialog(int status);
    ~RegisterAccountInterface();

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
};

#endif // REGISTERACCOUNTINTERFACE_H
