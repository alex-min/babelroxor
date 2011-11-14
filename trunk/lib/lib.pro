#-------------------------------------------------
#
# Project created by QtCreator 2011-11-08T15:03:02
#
#-------------------------------------------------

QT       += core gui

TARGET = lib
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iportablesocket.cpp \
    unixsocket.cpp \
    circularbuffer.cpp \
    network.cpp \
    crc.cpp \
    unixnetworkmanager.cpp \
    protocol.cpp \
    audio.cpp \
    networkroute.cpp \
    connectionslot.cpp \
    accountmanager.cpp \
    proxyslot.cpp \
    requestconnectionslot.cpp \
    testconnection.cpp \
    requestlink.cpp \
    proxyreceivedslot.cpp

HEADERS  += mainwindow.h \
    iportablesocket.h \
    portablelibrary.h \
    unixsocket.h \
    circularbuffer.h \
    network.h \
    islotinterface.h \
    crc.h \
    inetworkmanager.h \
    unixnetworkmanager.h \
    protocol.h \
    audio.h \
    networkroute.h \
    connectionslot.h \
    accountmanager.h \
    proxyslot.h \
    singleton.h \
    requestconnectionslot.h \
    testconnection.h \
    requestlink.h \
    proxyreceivedslot.h

FORMS    += mainwindow.ui
