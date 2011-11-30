QT       += core

QT       -= gui

TARGET = Speex
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


win32: LIBS += -L./Speex/lib/ -llibspeex

INCLUDEPATH += ./Speex/includes/
DEPENDPATH += ./Speex/includes/

win32: PRE_TARGETDEPS += ./Speex/lib/libspeex.lib

win32: LIBS += -L./Speex/lib/ -llibspeexdsp

INCLUDEPATH += ./Speex/includes/
DEPENDPATH += ./Speex/includes/

win32: PRE_TARGETDEPS += ./Speex/lib/libspeexdsp.lib

SOURCES += \
    Speex/My_Speex.cpp

HEADERS += \
    Speex/My_Speex.h

