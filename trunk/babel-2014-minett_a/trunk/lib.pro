#-------------------------------------------------
#
# Project created by QtCreator 2011-11-08T15:03:02
#
#-------------------------------------------------

QT       += core gui

TARGET = lib
TEMPLATE = app

SOURCES += ./lib/mainwindow.cpp \
    ./lib/iportablesocket.cpp \
    ./lib/unixsocket.cpp \
    ./lib/circularbuffer.cpp \
    ./lib/network.cpp \
    ./lib/crc.cpp \
    ./lib/unixnetworkmanager.cpp \
    ./lib/protocol.cpp \
    ./lib/audio.cpp \
    ./lib/networkroute.cpp \
    ./lib/connectionslot.cpp \
    ./lib/accountmanager.cpp \
    ./lib/proxyslot.cpp \
    ./lib/requestconnectionslot.cpp \
    ./lib/testconnection.cpp \
    ./lib/proxyreceivedslot.cpp \
    ./lib/account.cpp \
    ./lib/contactlist.cpp \
    ./lib/timerpool.cpp \
    ./lib/packet.cpp \
    ./lib/time.cpp \
    ./lib/windowssocket.cpp \
    ./lib/windowsnetworkmanager.cpp \
    ./lib/windowstime.cpp \
    ./lib/unixtime.cpp \
    ./lib/ScopedLock.cpp \
    ./lib/PThreadThread.cpp \
    ./lib/PThreadMutex.cpp

HEADERS  += ./lib/mainwindow.h \
    ./lib/iportablesocket.h \
    ./lib/portablelibrary.h \
    ./lib/unixsocket.h \
    ./lib/circularbuffer.h \
    ./lib/network.h \
    ./lib/islotinterface.h \
    ./lib/crc.h \
    ./lib/inetworkmanager.h \
    ./lib/unixnetworkmanager.h \
    ./lib/protocol.h \
    ./lib/audio.h \
    ./lib/networkroute.h \
    ./lib/connectionslot.h \
    ./lib/accountmanager.h \
    ./lib/proxyslot.h \
    ./lib/singleton.h \
    ./lib/requestconnectionslot.h \
    ./lib/testconnection.h \
    ./lib/proxyreceivedslot.h \
    ./lib/account.h \
    ./lib/contactlist.h \
    ./lib/timerpool.h \
    ./lib/packet.h \
    ./lib/pool.h \
    ./lib/time.h \
    ./lib/windowssocket.h \
    ./lib/windowsnetworkmanager.h \
    ./lib/windowstime.h \
    ./lib/unixtime.h \
    lib/islot.h \
    ./lib/PThreadMutex.h \
    ./lib/PThreadThread.h \
    ./lib/IThread.h \
    ./lib/IMutex.h \
    ./lib/Singleton.h \
    ./lib/ScopedLock.h \
    ./lib/PThreadThread.h \   
    lib/mutex.h

FORMS    += ./lib/mainwindow.ui

