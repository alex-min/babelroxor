QT       += core

QT       -= gui

TARGET = Speex
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


win32: LIBS += -L./Speex/lib/ -llibspeex

INCLUDEPATH += ./Speex/includes/speex/
DEPENDPATH += ./Speex/includes/speex/

win32: PRE_TARGETDEPS += ./Speex/lib/libspeex.lib

win32: LIBS += -L./Speex/lib/ -llibspeexdsp

INCLUDEPATH += ./Speex/includes/speex/
DEPENDPATH += ./Speex/includes/speex/

win32: PRE_TARGETDEPS += ./Speex/lib/libspeexdsp.lib

SOURCES += ./Speex/My_Speex.cpp

HEADERS += ./Speex/includes/speex/My_Speex.h





