#ifndef TALKWINDOWMANAGER_H
#define TALKWINDOWMANAGER_H

#include <QTabWidget>
#include <TalkWindow.h>
#include "singleton.h"

namespace Graphic
{
class TalkWindowManager : public QTabWidget
{
    Q_OBJECT

public:
    TalkWindowManager();
    void    addContact(QWidget *contactWindow, QIcon const &status);
    void    removeContact(std::string const &login);
    ~TalkWindowManager();

private:
    bool    checkIfContactExist(QWidget *contactWindow);

private slots:
    void    removeContact(int tabNum);
};
}

typedef Singleton<Graphic::TalkWindowManager>   TalkWindowManagerSingleton;

#endif // TALKWINDOWMANAGER_H
