#-------------------------------------------------
#
# Project created by QtCreator 2011-11-08T15:03:02
#
#-------------------------------------------------

SUBDIRS = lib
include(lib.pro)

INCLUDEPATH += ./lib

QT       += core gui

TARGET = server-babel-bin
TEMPLATE = app


SOURCES += ./server/main.cpp \
    server/connectionlogin.cpp \
    server/registeraccount.cpp

#HEADERS  += 

HEADERS += \
    server/connectionlogin.h \
    server/registeraccount.h




