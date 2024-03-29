#include "RegisterAccountInterface.h"
#include <QDebug>

RegisterAccountInterface::RegisterAccountInterface(QWidget *parent)
    : QDialog(parent)
{
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

void    RegisterAccountInterface::checkStatus()
{
    CustomButton *button = qobject_cast<CustomButton*>(sender());

    if (button->text() == "Ok")
        closeAccountDialog(1);
    else
        closeAccountDialog(0);
}

void    RegisterAccountInterface::closeAccountDialog(int status)
{
    if (status == 1)
    {
        std::string login = _loginLineEdit.text().toStdString();
        std::string password = _passwordLineEdit.text().toStdString();

        if (login == "" || password == "")
        {
            QMessageBox message;

            message.information(0, "Warning", "You must fill all the fields to create an account");
            message.setWindowModality(Qt::ApplicationModal);
        }
        else
        {
            qDebug() << _loginLineEdit.text();
            qDebug() << _passwordLineEdit.text();

            Q_UNUSED(login);
            Q_UNUSED(password);

            //we have to send a request to the server to ask him if we can create an account with this login and password

            close();

        }
    }
    else
        close();

}

RegisterAccountInterface::~RegisterAccountInterface()
{

}
