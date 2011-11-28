#include "MainWindow.h"
#include <QDebug>

namespace Graphic
{
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

    _dockWidget.setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::LeftDockWidgetArea, &_dockWidget);

    //_dockWidget.setVisible(false);

    _stackedWidget = new QStackedWidget(this);

    _accountInterface = AccountSingleton::getInstance();
    _centralWidget = CentralWidgetSingleton::getInstance();
    _dockWidgetContent = DockWidgetContentSingleton::getInstance();

    _stackedWidget->addWidget(_centralWidget);

  //   _stackedWidget->addWidget(_accountInterface);


    setCentralWidget(_stackedWidget);


    _dockWidget.setMinimumSize(400, 600);

    _dockWidget.setWidget(_dockWidgetContent);

    setWindowTitle("Babel client");
    setMinimumSize(800, 600);
}

MainWindow::~MainWindow()
{
    AccountSingleton::deleteInstance();
    CentralWidgetSingleton::deleteInstance();
    DockWidgetContentSingleton::deleteInstance();

    if (_stackedWidget)
        delete _stackedWidget;
}
}
