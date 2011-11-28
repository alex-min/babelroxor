#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T12:09:41
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH += ./lib
INCLUDEPATH += ./client

TARGET = babelClient
TEMPLATE = app


SOURCES += ./babelClient/DockWidgetContent.cpp \
    ./babelClient/CentralWidget.cpp \
    ./babelClient/CustomButton.cpp \
    ./babelClient/Account.cpp \
    ./babelClient/MainWindow.cpp \
    ./babelClient/RegisterAccount.cpp \
    ./babelClient/TalkWindow.cpp \
    ./babelClient/QtPopupMessage.cpp \
    ./babelClient/ListenServer.cpp \
    babelClient/TalkWindowManager.cpp

HEADERS  += ./babelClient/DockWidgetContent.h \
    ./babelClient/CentralWidget.h \
    ./babelClient/CustomButton.h \
    ./babelClient/InterfaceAccount.h \
    ./babelClient/Account.h \
    ./babelClient/MainWindow.h \
    ./babelClient/InterfaceRegisterAccount.h \
    ./babelClient/RegisterAccount.h \
    ./babelClient/TalkWindow.h \
    ./babelClient/InterfaceDockWidgetContent.h \
    ./babelClient/InterfaceCentralWidget.h \
    ./babelClient/InterfaceTalkWindow.h \
    ./babelClient/QtPopupMessage.h \
    ./babelClient/InterfacePopupMessage.h \
    ./babelClient/ListenServer.h \
    babelClient/TalkWindowManager.h


