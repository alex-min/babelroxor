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


SOURCES +=  ./portaudio/AudioCallback.cpp   \
            ./portaudio/AudioHandler.cpp    \
            ./portaudio/DecoderSpeex.cpp    \
            ./portaudio/EncoderSpeex.cpp



HEADERS +=  ./portaudio/AudioCallback.h     \
            ./portaudio/AudioHandler.h      \
            ./portaudio/DecoderSpeex.h      \
            ./portaudio/EncoderSpeex.h      \
            ./portaudio/UtiAudioCallback.hls.h


LIBS += -L./portaudio/ -L./Speex/lib

win32: LIBS += -L./portaudio/ -lportaudio_x86
unix: LIBS += -L/usr/local/lib/ -lportaudio -lspeex -lspeexdsp


INCLUDEPATH += ./portaudio/
INCLUDEPATH += ./Speex/
unix: INCLUDEPATH += /usr/local/include/speex
DEPENDPATH += ./portaudio/

win32: PRE_TARGETDEPS += ./portaudio/portaudio_x86.lib
