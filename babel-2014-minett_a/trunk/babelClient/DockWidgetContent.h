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
#include "InterfaceDockWidgetContent.h"
#include "singleton.h"
#include "QtPopupMessage.h"
#include "CallAnswer.h"

#define YES (16384)
#define NO (65536)

namespace Graphic
{
class DockWidgetContent : public QWidget, public InterfaceDockWidgetContent
{
    Q_OBJECT

signals:
    void    newClient(QString const &);
    void clientStatus(int, QList<std::string> const &);

public:
    DockWidgetContent();
    void    fillContactList();
    virtual std::string const &    getCurrentContactLogin();
    virtual std::string const &    getLogin();
    virtual void                   setLogin(std::string const &login);
    virtual void    updateClientAvatar(std::string const &filename);
    virtual void    showCallPopUp();
    virtual void    updateContactStatus(std::string const &login, int status);
    virtual void    addClientContact(std::string const &login);
    virtual void    removeCurrentClientContact(std::string const &login);
    ~DockWidgetContent();

public slots:
    void    addContact();
    void    removeContact();
    void    closeContactDialog(int finished);
    void    updateStatus(int status);
    void    chooseAvatar();
    void    updateAvatar(QString name);
    void    manageCall(int status);
    void    updateStatusForContact(QString const &login, int status);
    void    addContactToUpdateList(QString const &login);

private:
    bool    isContactAlreadyAdd(QString const &login);

private:
    QGridLayout _layout;
    QLabel      _avatar;
    QGroupBox   _contactBox;
    QVBoxLayout _contactBoxLayout;
    QListWidget _contactList;
    QLabel      _loginLabel;
    QHBoxLayout _buttonLayout;
    CustomButton _addContactButton;
    CustomButton _removeContactButton;
    QHBoxLayout  _statusLayout;
    QComboBox    _statusComboBox;
    CustomButton _avatarButton;
    std::string  _login;
    std::string      _currentContactLogin;
    QList<QListWidgetItem*> _contactItemList;
    QList<std::string>   _contactUpdateList;
};
}

typedef Singleton<Graphic::DockWidgetContent>   DockWidgetContentSingleton;

#endif // DOCKWIDGETCONTENT_H
