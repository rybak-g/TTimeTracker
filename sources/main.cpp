#include <QApplication>
#include <QQmlApplicationEngine>

#include <exception>
#include <iostream>

#include "TrayMenu.h"
#include "IServiceProvider.hpp"
#include "QServiceProvider.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QCoreApplication::setOrganizationName("TTimeTracker");
    QCoreApplication::setApplicationName("TimeTracker");
    QCoreApplication::setApplicationVersion("0.1");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qmlRegisterType<ServiceProvider::QmlWrapper>("PluginManager", 1, 0, "PluginManager");
    try {
        TrayMenu * tm = new TrayMenu(engine.rootObjects().at(0));
        (void)tm;
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unexpected error occured, exiting" << std::endl;
        return 1;
    }
    return app.exec();
}
