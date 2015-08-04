#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T21:50:19
#
#-------------------------------------------------

QT       += network

QT       -= gui

QMAKE_CXXFLAGS += -std=gnu++0x

TARGET = Phabricator
TEMPLATE = lib

DEFINES += PHABRICATOR_LIBRARY

SOURCES += PhabricatorServiceProvider.cpp \
    EntryPoint.cpp

HEADERS += PhabricatorServiceProvider.h\

unix {
    target.path = /usr/lib
    INSTALLS += target
}
