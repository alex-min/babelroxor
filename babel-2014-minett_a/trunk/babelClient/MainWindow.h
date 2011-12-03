#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QDockWidget>
#include <QStackedWidget>
#include "DockWidgetContent.h"
#include "CentralWidget.h"
#include "Account.h"
#include "singleton.h"

namespace Graphic
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void    closeConnection(QString const &, QString const &);

public:
    MainWindow(QWidget *parent = 0);
    void    init();
    ~MainWindow();

public slots:
    void    showWarningPopUp(QString const &title, QString const &text);
    void    showSuccessPopUp(QString const &title, QString const &text);
    void    switchOnConnectedState();

protected:
    virtual void closeEvent(QCloseEvent *);

private:
    QDockWidget *_dockWidget;
    Graphic::CentralWidget    *_centralWidget;
    Graphic::Account  *_accountInterface;
    Graphic::DockWidgetContent   *_dockWidgetContent;
    QStackedWidget      *_stackedWidget;
};
}

typedef Singleton<Graphic::MainWindow>   MainWindowSingleton;

#endif // MAINWINDOW_H
