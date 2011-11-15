#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QDockWidget>
#include "DockWidgetContent.h"
#include "CentralWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void    fillDockWidget();
    ~MainWindow();

private:
    QDockWidget *_dockWidget;
    CentralWidget     _centralWidget;
    DockWidgetContent   *_dockWidgetContent;
};

#endif // MAINWINDOW_H
