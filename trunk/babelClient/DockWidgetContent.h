#ifndef DOCKWIDGETCONTENT_H
#define DOCKWIDGETCONTENT_H

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QFileDialog>
#include "CustomButton.h"

class DockWidgetContent : public QWidget
{
    Q_OBJECT

public:
    DockWidgetContent();
    void    fillContactList();
    ~DockWidgetContent();

public slots:
    void    addContact();
    void    removeContact();
    void    closeContactDialog(int finished);
    void    updateClientStatus(QString status);
    void    chooseAvatar();
    void    updateAvatar(QString name);

private:
    QGridLayout _layout;
    QLabel      _avatar;
    QGroupBox   _contactBox;
    QVBoxLayout _contactBoxLayout;
    QListWidget _contactList;
    QLabel      _login;
    QHBoxLayout _buttonLayout;
    CustomButton _addContactButton;
    CustomButton _removeContactButton;
    QHBoxLayout  _statusLayout;
    QComboBox    _statusComboBox;
    CustomButton _avatarButton;
};

#endif // DOCKWIDGETCONTENT_H
