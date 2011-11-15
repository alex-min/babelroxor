#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *myMenuBar = menuBar();
    QMenu *fileMenu = myMenuBar->addMenu("File");
    QMenu *EditionMenu = myMenuBar->addMenu("Edition");
    QMenu *helpMenu = myMenuBar->addMenu("Help");

    myMenuBar->setObjectName("myMenuBar");
    fileMenu->setObjectName("myFileMenu");
    EditionMenu->setObjectName("myEditionMenu");
    helpMenu->setObjectName("myHelpMenu");


    _dockWidget = new QDockWidget;

    _dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::LeftDockWidgetArea, _dockWidget);

    setCentralWidget(&_centralWidget);
    _dockWidget->setMinimumSize(400, 600);

    fillDockWidget();
    setMinimumSize(800, 600);
}

void    MainWindow::fillDockWidget()
{
    _dockWidgetContent = new DockWidgetContent;

    _dockWidget->setWidget(_dockWidgetContent);
}

MainWindow::~MainWindow()
{

}
