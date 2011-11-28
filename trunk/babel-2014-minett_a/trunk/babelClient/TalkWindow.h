#ifndef TALKWINDOW_H
#define TALKWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QToolBar>
#include <QGridLayout>
#include <QAction>
#include <QIcon>
#include <QToolButton>
#include <QFontComboBox>
#include <QWidget>
#include "DockWidgetContent.h"
#include "InterfaceTalkWindow.h"
#include "status.h"

namespace Graphic
{
class TalkWindow : public QWidget, InterfaceTalkWindow
{
    Q_OBJECT

public:
    TalkWindow(QWidget *parent = 0);
    void    setContactLogin(std::string const &login);
    std::string const & getContactLogin();
    ~TalkWindow();

public slots:
    void    changeBold();
    void    changeUnderline();
    void    changeFamily(QString const &name);
    virtual void    sendTextToServer();

protected:
    void    closeEvent(QCloseEvent *);

private:
    QTextEdit   _textView;
    QTextEdit   _textToSend;
    QToolBar    _toolBar;
    QPushButton _sendButton;
    QGridLayout _layout;
    QToolButton _boldToolButton;
    QToolButton _underlineToolButton;
    QFontComboBox   _familyComboBox;
    bool        _bold;
    bool        _underlined;
    DockWidgetContent *_dockWidgetContent;
    std::string _contactLogin;
};
}

#endif // TALKWINDOW_H
