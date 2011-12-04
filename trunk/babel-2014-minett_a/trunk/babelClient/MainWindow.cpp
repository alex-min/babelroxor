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
    setMinimumSize(800, 700);

    connect(ListenServerSingleton::getInstance(), SIGNAL(connected()), this, SLOT(switchOnConnectedState()));
    connect(ListenServerSingleton::getInstance(), SIGNAL(warningPopUp(QString const&,QString const&)),
            this, SLOT(showWarningPopUp(QString const&,QString const&)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(successPopUp(QString const&,QString const&)),
            this, SLOT(showSuccessPopUp(QString const&,QString const&)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(contactStatusChanged(QString,int)), _dockWidgetContent, SLOT(updateStatusForContact(QString,int)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(callOccured(QString const &, unsigned int)), _centralWidget, SLOT(showCallPopUp(QString const &, unsigned int)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(callFail()), _centralWidget, SLOT(showFailCall()));
    connect(ListenServerSingleton::getInstance(), SIGNAL(newContactToUpdateList(QString const &)), _dockWidgetContent, SLOT(addContactToUpdateList(QString const &)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(textMessageChanged(QString const &)), _centralWidget, SLOT(updateTalkWindowText(QString const&)));
}

void    MainWindow::closeEvent(QCloseEvent *)
{
    if (_stackedWidget->currentWidget() == _centralWidget)
        emit closeConnection(QString(_accountInterface->getLogin().c_str()), QString(_accountInterface->getPassword().c_str()));

    deleteLater();
}

void    MainWindow::showWarningPopUp(QString const &title, QString const &text)
{
    Graphic::QtPopUpMessage *popup = Graphic::QtPopUpMessage::createPopUp(Graphic::QtPopUpMessage::WARNING,
                                                                          title.toStdString(), text.toStdString());
    popup->setIconPixmap(QPixmap("../trunk/images/warning.png"));
    _accountInterface->resetFields();

    popup->show();

    QObject::connect(popup, SIGNAL(finished(int)), popup, SLOT(deleteLater()));
}

void    MainWindow::showSuccessPopUp(QString const &title, QString const &text)
{
    Graphic::QtPopUpMessage *popup = Graphic::QtPopUpMessage::createPopUp(Graphic::QtPopUpMessage::INFORMATION,
                                                                          title.toStdString(), text.toStdString());
    popup->setIconPixmap(QPixmap("../trunk/images/success.png"));
    _accountInterface->resetFields();

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

    //if (_stackedWidget)
    //  delete _stackedWidget;
}
}
