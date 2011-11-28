#-------------------------------------------------
#
# Project created by QtCreator 2011-11-08T15:03:02
#
#-------------------------------------------------

SUBDIRS += lib
SUBDIRS += babelClient

include(lib.pro)
include(babelClient.pro)

INCLUDEPATH += ./lib
INCLUDEPATH += ./babelClient

QT       += core gui

TARGET = client-babel-bin
TEMPLATE = app


SOURCES += ./client/main.cpp \
    client/audioslot.cpp \
    client/connectionlogin.cpp \
    client/protocolinterfaceslot.cpp \
    client/requestlink.cpp \
    client/status.cpp \
    client/StatusAnswer.cpp \
    client/connecttome.cpp \
    client/CallAnswer.cpp \
    client/audiothread.cpp

#HEADERS  +=

HEADERS += \
    client/audioslot.h \
    client/connectionlogin.h \
    client/protocolinterfaceslot.h \
    client/requestlink.h \
    client/status.h \
    client/StatusAnswer.h \
    client/connecttome.h \
    client/CallAnswer.h \
    client/audiothread.h
