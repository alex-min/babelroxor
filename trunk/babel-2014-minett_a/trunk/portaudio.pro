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

LIBS += -L./portaudio/ -lportaudio

win32: LIBS += -L./portaudio/ -lportaudio_x86
unix: LIBS += -L./usr/local/lib/ -lportaudio


INCLUDEPATH += ./portaudio/
DEPENDPATH += ./portaudio/

win32: PRE_TARGETDEPS += ./portaudio/portaudio_x86.lib
