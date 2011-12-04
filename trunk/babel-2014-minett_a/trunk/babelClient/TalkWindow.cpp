#include "TalkWindow.h"

namespace Graphic
{
TalkWindow::TalkWindow(QWidget *parent)
    : QWidget(parent)
{
    _bold = false;
    _underlined = false;
    _dockWidgetContent = DockWidgetContentSingleton::getInstance();

    setObjectName("talkWindow");

    _textView.setReadOnly(true);
    _sendButton.setText("Send");

    _sendButton.setMinimumSize(600, 30);
    _sendButton.setObjectName("talkWindowSend");
    _boldToolButton.setIcon(QIcon("../trunk/images/bold.png"));
    _underlineToolButton.setIcon(QIcon("../trunk/images/underline.png"));

    _toolBar.setMinimumSize(600, 40);

    _toolBar.addWidget(&_boldToolButton);
    _toolBar.addWidget(&_underlineToolButton);
    _toolBar.addWidget(&_familyComboBox);

    _layout.addWidget(&_textView, 0, 0, 1, 2);
    _layout.addWidget(&_toolBar, 1, 0, 1, 2);
    _layout.addWidget(&_textToSend, 2, 0, 1, 2);
    _layout.addWidget(&_sendButton, 3, 0, 1, 2);

   // setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    setMinimumSize(600, 200);

    setLayout(&_layout);

    connect(&_boldToolButton, SIGNAL(clicked()), this, SLOT(changeBold()));
    connect(&_underlineToolButton, SIGNAL(clicked()), this, SLOT(changeUnderline()));
    connect(&_familyComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeFamily(QString const&)));
    connect(&_sendButton, SIGNAL(clicked()), this, SLOT(sendTextToServer()));
}

void    TalkWindow::setContactLogin(std::string const &login)
{
    _contactLogin = login;

    setWindowTitle(QString(_contactLogin.c_str()));
}

std::string const &TalkWindow::getContactLogin()
{
    return (_contactLogin);
}

void    TalkWindow::updateText(const std::string &text)
{
    _textView.setText(_textView.toPlainText() + "\n" + QString(text.c_str()));
}

void    TalkWindow::sendTextToServer()
{
    std::string login = _dockWidgetContent->getLogin();
    std::string text = _textToSend.toPlainText().toStdString();

    _textToSend.clear();
    _textView.setText(_textView.toPlainText() + "\n" + QString(login.c_str()) + ": " + QString(text.c_str()));

    text = login + ": " + text;

    emit textToSend(QString(_contactLogin.c_str()), QString(text.c_str()));
}

void    TalkWindow::changeFamily(QString const &name)
{
    _textToSend.setFontFamily(name);
}

void    TalkWindow::changeUnderline()
{
     _underlined = !_underlined;

    _textToSend.setFontUnderline(_underlined);
}

void    TalkWindow::changeBold()
{
    if (_bold)
    {
       _textToSend.setFontWeight(QFont::Normal);
       _bold = false;
    }
    else
    {
        _textToSend.setFontWeight(QFont::Bold);
        _bold = true;
    }
}

void    TalkWindow::closeEvent(QCloseEvent *)
{
    // do a request to the server to hang up with the current contact
}

TalkWindow::~TalkWindow()
{

}
}
