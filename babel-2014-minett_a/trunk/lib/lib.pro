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
    proxyreceivedslot.cpp \
    account.cpp \
    contactlist.cpp \
    timerpool.cpp \
    packet.cpp \
    time.cpp \
    windowssocket.cpp \
    windowsnetworkmanager.cpp \
    unixtime.cpp

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
    proxyreceivedslot.h \
    account.h \
    contactlist.h \
    timerpool.h \
    packet.h \
    pool.h \
    time.h \
    windowssocket.h \
    windowsnetworkmanager.h \
    unixtime.h

FORMS    += mainwindow.ui
