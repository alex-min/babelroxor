#-------------------------------------------------
#
# Project created by QtCreator 2011-11-14T17:42:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = portaudio
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += ./portaudio/portaudio.cpp



HEADERS += ./portaudio/portaudio.h \
    ./portaudio/portaudio2.h



win32: LIBS += -L./portaudio/ -lportaudio_x86

INCLUDEPATH += ./portaudio/
DEPENDPATH += ./portaudio/

win32: PRE_TARGETDEPS += ./portaudio/portaudio_x86.lib
