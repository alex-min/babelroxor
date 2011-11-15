#include "DockWidgetContent.h"
#include <QDebug>

DockWidgetContent::DockWidgetContent()
{
    _login.setText("Profil_j");
    _login.setObjectName("login");

    _statusComboBox.addItem(QIcon("./status_connected.png"), "Online");
    _statusComboBox.addItem(QIcon("./status_busy.png"), "Busy");
    _statusComboBox.addItem(QIcon("./status_deconnected.png"), "Offline");

    _statusLayout.addWidget(&_login);
    _statusLayout.setSpacing(20);
    _statusLayout.addWidget(&_statusComboBox);

    _avatar.setPixmap(QPixmap("./anonymous.png"));
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
    // _addContactButton.setIcon(QPixmap("./new_contact.png"));
    //_removeContactButton.setIcon(QPixmap("./remove_contact.png"));
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
    connect(&_statusComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateClientStatus(QString)));
    connect(&_avatarButton, SIGNAL(clicked()), this, SLOT(chooseAvatar()));
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
    // do a request to update the avatar in the server

    _avatar.setPixmap(QPixmap(name));
}

void    DockWidgetContent::updateClientStatus(QString status)
{
    qDebug() << "Status changed: \n" << "New Status: " << status;

    // We have to do a request to the server to tell him the client status has just changed
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

    dialog->setFixedSize(300, 100);
    dialog->show();

    connect(valid, SIGNAL(clicked()), dialog, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), dialog, SLOT(close()));
    connect(dialog, SIGNAL(finished(int)), this, SLOT(closeContactDialog(int)));
}

void    DockWidgetContent::closeContactDialog(int finished)
{
    QDialog *dialog = qobject_cast<QDialog*>(sender());
    QLayout *l = dialog->layout();

    if (finished == 1)
    {
        QLineEdit *loginLineEdit = qobject_cast<QLineEdit*>(l->itemAt(1)->widget());
        std::string login = loginLineEdit->text().toStdString();

        Q_UNUSED(login);

        // request to server to ask if we can add the Contact
        // if yes, so we add the contact in the list
        // what is his status so that we can set the icon to the QListWidgetItem to show it
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
    //ask to the server if we can remove the contact selected
}

void    DockWidgetContent::fillContactList()
{
    // ask the contact list of the client by requests to the server

    _contactList.addItem(new QListWidgetItem(QIcon("./status_deconnected"), "Rintintin"));

}

DockWidgetContent::~DockWidgetContent()
{

}

