#include "TalkWindowManager.h"
#include <QDebug>

namespace Graphic
{
TalkWindowManager::TalkWindowManager()
{
    setWindowTitle("Contact Manager");

    setTabsClosable(true);

    setFixedSize(600, 500);

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(removeContact(int)));
}

TalkWindow* TalkWindowManager::getWindowFromLogin(std::string const &login)
{
    for (int i = 0; i < count(); i++)
    {
        TalkWindow *itemWindow = dynamic_cast<TalkWindow*>(widget(i));

        if (itemWindow->getContactLogin() == login)
            return (itemWindow);
    }
}

bool    TalkWindowManager::checkIfContactExist(QWidget *contactWindow)
{
    TalkWindow *newItem = dynamic_cast<TalkWindow*>(contactWindow);

    for (int i = 0; i < count(); i++)
    {
        TalkWindow *item = dynamic_cast<TalkWindow*>(widget(i));

        if (item->getContactLogin() == newItem->getContactLogin())
            return (true);
    }

    return (false);
}

void TalkWindowManager::addContact(QWidget *contactWindow, QIcon const &status)
{
    if (!checkIfContactExist(contactWindow))
    {
        addTab(contactWindow, status, dynamic_cast<TalkWindow*>(contactWindow)->getContactLogin().c_str());
        contactWindow->setFocus();
    }
}

void TalkWindowManager::removeContact(int tabNum)
{
    QWidget *item = widget(tabNum);
    TalkWindow *itemWindow = dynamic_cast<TalkWindow*>(item);

    removeTab(tabNum);

    emit tabClosed(QString(itemWindow->getContactLogin().c_str()));

    if (!count())
        close();

    delete item;
}

void TalkWindowManager::removeContact(std::string const &login)
{
    for (int i = 0; i < count(); i++)
    {
        QWidget *item = widget(i);
        TalkWindow *itemWindow = dynamic_cast<TalkWindow*>(item);

        if (itemWindow->getContactLogin() == login)
        {
            removeTab(i);

            delete item;

            if (!count())
                close();

            break;
        }
    }
}

TalkWindowManager::~TalkWindowManager()
{

}
}

