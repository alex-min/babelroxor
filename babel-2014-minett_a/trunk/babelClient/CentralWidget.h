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

namespace Graphic
{
class CentralWidget : public QWidget, InterfaceCentralWidget
{
    Q_OBJECT

public:

    CentralWidget();
    virtual void    callClient(std::string const &login);
    virtual void    hangUpClient(std::string const &login);
    ~CentralWidget();

public slots:
    void    call();
    void    hangUp();

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