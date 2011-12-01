#include "DockWidgetContent.h"
#include "ListenServer.h"
#include <QDebug>

namespace Graphic
{
DockWidgetContent::DockWidgetContent()
{
    _loginLabel.setText("Profil_j");
    _loginLabel.setObjectName("login");
    _login = "Profil_j";

    _statusComboBox.addItem(QIcon("../trunk/images/status_connected.png"), "Online");
    _statusComboBox.addItem(QIcon("../trunk/images/status_busy.png"), "Busy");
    _statusComboBox.addItem(QIcon("../trunk/images/status_deconnected.png"), "Offline");

    _statusLayout.addWidget(&_loginLabel);
    _statusLayout.setSpacing(20);
    _statusLayout.addWidget(&_statusComboBox);

    _avatar.setPixmap(QPixmap("../trunk/images/anonymous.png"));
    _avatar.setAlignment(Qt::AlignCenter);
    _avatar.setMinimumSize(200, 700 / 4);
    _avatar.setStyleSheet("background-color: black");
    _avatar.setObjectName("avatar");

    _avatarButton.setShape(CustomButton::ROUND);
    _avatarButton.setRadius(8.0, 8.0);
    _avatarButton.setBold(true);
    _avatarButton.setText("...");

    fillContactList();

    _contactBox.setTitle("Your contact list :");
    _contactBox.setFlat(true);
    _contactBox.setObjectName("contactList");
    _contactBoxLayout.addWidget(&_contactList);
    _contactBox.setLayout(&_contactBoxLayout);

    _addContactButton.setShape(CustomButton::ROUND);
    _removeContactButton.setShape(CustomButton::ROUND);
    _addContactButton.setRadius(8.0, 8.0);
    _removeContactButton.setRadius(8.0, 8.0);
    _addContactButton.setText("Add Contact");
    _removeContactButton.setText("Remove Contact");
    _addContactButton.setBold(true);
    _removeContactButton.setBold(true);

    _buttonLayout.addWidget(&_addContactButton, 0, Qt::AlignTop);
    _buttonLayout.addWidget(&_removeContactButton, 0, Qt::AlignTop);

    _layout.addLayout(&_statusLayout, 0, 0, 1, 1, Qt::AlignHCenter);
    _layout.addWidget(&_avatar, 1, 0, 1, 1, Qt::AlignTop);
    _layout.addWidget(&_avatarButton, 1, 1, 1, 1, Qt::AlignTop);
    _layout.addWidget(&_contactBox, 2, 0, 1, 1);
    _layout.addLayout(&_buttonLayout, 3, 0);

    setLayout(&_layout);

    connect(&_addContactButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(&_removeContactButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(&_statusComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStatus(int)));
    connect(&_avatarButton, SIGNAL(clicked()), this, SLOT(chooseAvatar()));
}

void    DockWidgetContent::updateStatusForContact(const QString &login, int status)
{
        updateContactStatus(login.toStdString(), status);
}

void    DockWidgetContent::setLogin(const std::string &login)
{
    _loginLabel.setText(QString(login.c_str()));
    _login = login;
}

void    DockWidgetContent::showCallPopUp()
{
    QtPopUpMessage *popUp = QtPopUpMessage::createPopUp(QtPopUpMessage::INFORMATION,
                                                        "Call",
                                                        "Do you want to accept the call of " +
                                                        CallAnswerSingleton::getInstance()->getLogin() + " ?");

    popUp->setButtonType(QtPopUpMessage::AcceptButton | QtPopUpMessage::RefuseButton);
    popUp->show();

    connect(popUp, SIGNAL(finished(int)), this, SLOT(manageCall(int)));
}

void    DockWidgetContent::manageCall(int status)
{
//    QtPopUpMessage *popup = qobject_cast<QtPopUpMessage*>(sender());
//    Status *stat =  StatusSingleton::getInstance();

//    if (status == YES)
//        stat->sendCallStatus(CallAnswerSingleton::getInstance()->getLogin(), 1);
//    else if (status == NO)
//        stat->sendCallStatus(CallAnswerSingleton::getInstance()->getLogin(), 0);

//    CallAnswerSingleton::getInstance()->resetLogin();

//    popup->deleteLater();
}

std::string const &    DockWidgetContent::getLogin()
{
    return (_login);
}

void    DockWidgetContent::updateClientAvatar(std::string const &filename)
{
    Q_UNUSED(filename);

    // do a request to update the avatar in the server
}

void    DockWidgetContent::updateClientStatus(int status)
{
    emit clientStatus(QString(_login.c_str()), status);
}

void    DockWidgetContent::updateContactStatus(std::string const &login, int status)
{
    foreach (QListWidgetItem *item, _contactItemList)
    {
        QString log = QString(login.c_str());

        if (item->text() == log)
        {
            QIcon ico;

            if (status == -1)
                return ;

            ico = _statusComboBox.itemIcon(status);
            item->setIcon(ico);
        }
    }
}

void    DockWidgetContent::addClientContact(std::string const &login)
{
    emit newClient(QString(login.c_str()));
}

void    DockWidgetContent::removeCurrentClientContact(std::string const &login)
{
    Q_UNUSED(login);

    //ask to the server if we can remove the contact selected
}

std::string const &    DockWidgetContent::getCurrentContactLogin()
{
    _currentContactLogin = "";
    QListWidgetItem *item = _contactList.currentItem();

    if (item)
        _currentContactLogin = item->text().toStdString();

    return (_currentContactLogin);
}

void    DockWidgetContent::chooseAvatar()
{
    QFileDialog *fileDialog = new QFileDialog;

    QStringList filters;
    filters << "*.png" << "*.jpeg" << "*.jpg";
    fileDialog->setNameFilters(filters);


    fileDialog->setWindowModality(Qt::ApplicationModal);

    fileDialog->show();

    connect(fileDialog, SIGNAL(fileSelected(QString)), this, SLOT(updateAvatar(QString)));
}

void    DockWidgetContent::updateAvatar(QString name)
{
    _avatar.setPixmap(QPixmap(name));

    updateClientAvatar(name.toStdString());
}

void    DockWidgetContent::updateStatus(int status)
{
    updateClientStatus(status);
}

void    DockWidgetContent::addContact()
{
    QDialog *dialog = new QDialog;
    CustomButton *valid = new CustomButton("Ok", CustomButton::ROUND);
    CustomButton *cancel = new CustomButton("Cancel", CustomButton::ROUND);
    QLabel *t = new QLabel("To add a contact you have to enter his login.");
    QLineEdit *loginLineEdit = new QLineEdit;
    QGridLayout *l = new QGridLayout;


    valid->setRadius(8.0, 8.0);
    valid->setBold(true);
    cancel->setRadius(8.0, 8.0);
    cancel->setBold(true);

    l->addWidget(t, 0, 0, 1, 2);
    l->addWidget(loginLineEdit, 1, 0, 1, 2);
    l->addWidget(valid, 2, 0);
    l->addWidget(cancel, 2, 1);

    dialog->setLayout(l);

    dialog->setWindowTitle("Add a contact");
    dialog->setWindowModality(Qt::ApplicationModal);

    dialog->setFixedSize(350, 100);
    dialog->setObjectName("addContact");
    t->setObjectName("infoAddContact");
    dialog->show();

    connect(valid, SIGNAL(clicked()), dialog, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), dialog, SLOT(close()));
    connect(dialog, SIGNAL(finished(int)), this, SLOT(closeContactDialog(int)));
}

bool    DockWidgetContent::isContactAlreadyAdd(QString const &login)
{
    foreach (QListWidgetItem *item, _contactItemList)
    {
        if (item->text() == login)
            return (true);
    }

    return (false);
}

void    DockWidgetContent::closeContactDialog(int finished)
{
    QDialog *dialog = qobject_cast<QDialog*>(sender());
    QLayout *l = dialog->layout();

    if (finished == 1)
    {
        QLineEdit *loginLineEdit = qobject_cast<QLineEdit*>(l->itemAt(1)->widget());
        std::string login = loginLineEdit->text().toStdString();

        if (!isContactAlreadyAdd(loginLineEdit->text()))
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon("../trunk/images/status_deconnected"), loginLineEdit->text());

            _contactList.addItem(item);
            _contactItemList.append(item);

            addClientContact(login);
        }
    }

    for (int i = l->count(); i > 0; i--)
    {
        QLayoutItem *item = l->itemAt(i);

        l->removeItem(item);

        delete item;

        item = 0;
    }

    delete l;
    dialog->deleteLater();
}


void DockWidgetContent::removeContact()
{
    QListWidgetItem *item = _contactList.currentItem();

    if (item)
    {
        std::string login = item->text().toStdString();

        _contactItemList.removeOne(item);
        _contactList.removeItemWidget(item);

        delete item;

        removeCurrentClientContact(login);
    }
}

void    DockWidgetContent::fillContactList()
{
    // ask the contact list of the client by requests to the server

    QListWidgetItem *item = new QListWidgetItem(QIcon("../trunk/images/status_deconnected"), "Rintintin");

    _contactList.addItem(item);
    _contactItemList.append(item);

}

DockWidgetContent::~DockWidgetContent()
{

}
}
