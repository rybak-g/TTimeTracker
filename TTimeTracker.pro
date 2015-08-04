TEMPLATE = app

QT += qml quick widgets

QMAKE_CXXFLAGS += -std=gnu++0x -D_DEBUG

SOURCES += \
    sources/main.cpp \
    sources/TrayMenu.cpp \
    sources/TimerEvent.cpp

RESOURCES += qml/qml.qrc \
    icons/icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += \
    include

HEADERS += \
    include/DlLoader.hpp \
    include/DlManager.hpp \
    include/IServiceProvider.hpp \
    include/Task.h \
    include/TTask.hpp \
    include/Dll.h \
    include/TSetting.hpp \
    include/TrayMenu.h \
    include/StringSetting.h \
    include/TimerEvent.h \
    include/QServiceProvider.h
