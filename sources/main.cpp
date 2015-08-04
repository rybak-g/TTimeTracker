#include <QApplication>
#include <QQmlApplicationEngine>

#include <exception>
#include <iostream>

#include "TrayMenu.h"
#include "IServiceProvider.hpp"
#include "DlManager.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    DlManager<const char *, ServiceProvider::Interface> manager;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    manager.loadFromDir((QCoreApplication::applicationDirPath()+"/plugins").toStdString());

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
