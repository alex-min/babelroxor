#include "MainWindow.h"
#include "ListenServer.h"

#include <QDebug>

namespace Graphic
{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

}

void    MainWindow::init()
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

    _dockWidget->setVisible(false);

    _stackedWidget = new QStackedWidget;

    _accountInterface = AccountSingleton::getInstance();
    _centralWidget = CentralWidgetSingleton::getInstance();
    _dockWidgetContent = DockWidgetContentSingleton::getInstance();

    _stackedWidget->addWidget(_accountInterface);
    _stackedWidget->addWidget(_centralWidget);

    setCentralWidget(_stackedWidget);

    _dockWidget->setWidget(_dockWidgetContent);

    _dockWidget->setMinimumSize(400, 600);

    addDockWidget(Qt::LeftDockWidgetArea, _dockWidget, Qt::Vertical);

    setWindowTitle("Babel Client");
    setMinimumSize(800, 600);

    connect(ListenServerSingleton::getInstance(), SIGNAL(connected()), this, SLOT(switchOnConnectedState()));

    connect(ListenServerSingleton::getInstance(), SIGNAL(connectionPopUpWarning(QString const&,QString const&)),
            this, SLOT(showConnectionPopUpWarning(QString const&,QString const&)));
}

void    MainWindow::showConnectionPopUpWarning(QString const &title, QString const &text)
{
    Graphic::QtPopUpMessage *popup = Graphic::QtPopUpMessage::createPopUp(Graphic::QtPopUpMessage::WARNING,
                                                                               title.toStdString(), text.toStdString());

    popup->show();

  QObject::connect(popup, SIGNAL(finished(int)), popup, SLOT(deleteLater()));
}

void    MainWindow::switchOnConnectedState()
{
    _dockWidgetContent->setLogin(_accountInterface->getLogin());
    _dockWidget->setVisible(true);
    _stackedWidget->setCurrentWidget(_centralWidget);
}

MainWindow::~MainWindow()
{
    AccountSingleton::deleteInstance();
    CentralWidgetSingleton::deleteInstance();
    DockWidgetContentSingleton::deleteInstance();

    delete _dockWidget;

    if (_stackedWidget)
        delete _stackedWidget;
}
}
