#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include "CustomButton.h"
#include "DockWidgetContent.h"
#include "TalkWindow.h"
#include "InterfaceCentralWidget.h"
#include "singleton.h"
#include "TalkWindowManager.h"
#include "protocol.h"

namespace Graphic
{
class CentralWidget : public QWidget, InterfaceCentralWidget
{
    Q_OBJECT

signals:
    void newLink(QString const &);
    void textChanged(QString const &, QString const &);
    void needOpenTalkWindow(QString const &);

public:

    CentralWidget();
    virtual void    callClient(std::string const &login);
    virtual void    hangUpClient(std::string const &login);
    void            showCurrentContacts();
    void            showCurrentContacts(std::string const &);
    ~CentralWidget();
    void            emitNeedOpenTalkWindow(QString const &);


public slots:
    void    addTalkWindow(QString const &);
    void    call();
    void    hangUp();
    void    showCallPopUp(QString const &login, unsigned id);
    void    checkIfCallIsAccepted(int status);
    void    showFailCall();
    void    updateTalkWindowText(QString const &text);


private:

    QGridLayout _layout;
    CustomButton    _callButton;
    CustomButton    _hangUpButton;
    DockWidgetContent   *_dockWidgetContent;
    TalkWindowManager   *_windowManager;
};
}

typedef Singleton<Graphic::CentralWidget>  CentralWidgetSingleton;

#endif // CENTRALWIDGET_H
