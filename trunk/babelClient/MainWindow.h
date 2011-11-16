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
#include "AccountInterface.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QDockWidget _dockWidget;
    CentralWidget     _centralWidget;
    AccountInterface  _accountInterface;
    DockWidgetContent   _dockWidgetContent;
    QStackedWidget      *_stackedWidget;
};

#endif // MAINWINDOW_H
