#include "CentralWidget.h"
#include "requestlink.h"
#include <QDebug>
#include <requestlink.h>
#include "ListenServer.h"

namespace Graphic
{
CentralWidget::CentralWidget()
{
    _windowManager = TalkWindowManagerSingleton::getInstance();

    _callButton.setShape(CustomButton::ROUND);
    _hangUpButton.setShape(CustomButton::ROUND);

    _callButton.setText("Call");
    _hangUpButton.setText("HangUp"
                          );

    _callButton.setRadius(8.0, 8.0);
    _hangUpButton.setRadius(8.0, 8.0);

    _callButton.setIcon(QPixmap("../trunk/images/call.png"));
    _hangUpButton.setIcon(QPixmap("../trunk/images/hang_up.png"));

    _callButton.setBold(true);
    _hangUpButton.setBold(true);

    _layout.addWidget(&_callButton, 0, 0, Qt::AlignTop);
    _layout.addWidget(&_hangUpButton, 0, 1, Qt::AlignTop);

    _dockWidgetContent = DockWidgetContentSingleton::getInstance();

    setLayout(&_layout);

    connect(&_callButton, SIGNAL(clicked()), this, SLOT(call()));
    connect(&_hangUpButton, SIGNAL(clicked()), this, SLOT(hangUp()));
}

void    CentralWidget::showFailCall()
{
    QtPopUpMessage *popUp = QtPopUpMessage::createPopUp(QtPopUpMessage::WARNING, "Call", "Your call has failed");

    popUp->setIconPixmap(QPixmap("../trunk/images/warning.png"));
    popUp->show();

    connect(popUp, SIGNAL(finished(int)), this, SLOT(deleteLater()));
}

void    CentralWidget::showCallPopUp(QString const &login)
{
    QtPopUpMessage *popUp = QtPopUpMessage::createPopUp(QtPopUpMessage::WARNING, "Call", "You have a call request of " + login.toStdString());

    popUp->setIconPixmap(QPixmap("../trunk/images/warning.png"));
    popUp->setButtonType(QtPopUpMessage::AcceptButton | QtPopUpMessage::RefuseButton);
    popUp->setLogin(login.toStdString());
    popUp->show();

    connect(popUp, SIGNAL(finished(int)), this, SLOT(checkIfCallIsAccepted(int)));
}

void    CentralWidget::checkIfCallIsAccepted(int status)
{
    QtPopUpMessage *popUp = qobject_cast<QtPopUpMessage*>(sender());

    if (status == QMessageBox::Yes)
        showCurrentContacts();

    popUp->deleteLater();
}

void    CentralWidget::callClient(std::string const &login)
{
    // AudioThreadSingleton::getInstance()->addLogin("lol");
    emit newLink(QString(login.c_str()));
    //    RequestLinkSingleton::getInstance()->createNewLink(login);
    Q_UNUSED(login);
}

void    CentralWidget::hangUpClient(std::string const &login)
{
    Q_UNUSED(login);
}

void    CentralWidget::call()
{
    std::string const & currentContactLogin = _dockWidgetContent->getCurrentContactLogin();

    callClient(currentContactLogin);
}

void    CentralWidget::showCurrentContacts()
{
    std::string const & currentContactLogin = _dockWidgetContent->getCurrentContactLogin();

    _windowManager->show();
    _windowManager->activateWindow();

    if (!currentContactLogin.empty())
    {
        TalkWindow *w = new TalkWindow;

        w->setContactLogin(currentContactLogin);
        _windowManager->addContact(w, QIcon("../trunk/images/onCall.png"));
    }
}

void    CentralWidget::hangUp()
{
    std::string const & currentContactLogin = _dockWidgetContent->getCurrentContactLogin();

    _windowManager->removeContact(currentContactLogin);

    hangUpClient(currentContactLogin);
}

CentralWidget::~CentralWidget()
{
    TalkWindowManagerSingleton::deleteInstance();
}
}
