TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    TrayMenu.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    DlLoader.hpp \
    DlManager.hpp \
    IServiceProvider.hpp \
    Task.h \
    TTask.hpp \
    Dll.h \
    TSetting.hpp \
    TrayMenu.h \
    StringSetting.h
