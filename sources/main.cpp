#include <QApplication>
#include <QQmlApplicationEngine>

#include <exception>
#include <iostream>

#include "TrayMenu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    try {
        TrayMenu * tm = new TrayMenu(engine.rootObjects().at(0));
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        return 1;
    }
    return app.exec();
}
