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

    removeTab(tabNum);

    // send a message to the server to indicate the communication has just hang up

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

            // send a message to the server to indicate the communication has just hang up

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

