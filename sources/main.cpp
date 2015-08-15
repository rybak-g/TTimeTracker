#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTime>

#include <exception>
#include <iostream>

#include "TrayMenu.h"
#include "IServiceProvider.hpp"
#include "QServiceProvider.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
#ifndef _DEBUG
    Q_UNUSED(context);
#endif
    QByteArray localMsg = msg.toLocal8Bit();
    std::cerr << QTime::currentTime().toString("[hh:mm:ss.zzz] ").toStdString();
    switch (type) {
    case QtDebugMsg:
        std::cerr << "[Debug]   > ";
        break;
    case QtInfoMsg:
        std::cerr << "[Info]    > ";
        break;
    case QtWarningMsg:
        std::cerr << "[Warning] > ";
        break;
    case QtCriticalMsg:
        std::cerr << "[Critical]> ";
        break;
    case QtFatalMsg:
        std::cerr << "[Fatal]   > ";
        abort();
    }
    std::cerr << localMsg.data();
#ifdef _DEBUG
    std::cerr << " (" << context.file << ":" << context.line << ", " << context.function << ")" << std::endl;
#else
    std::cerr << std::endl;
#endif
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QCoreApplication::setOrganizationName("TTimeTracker");
    QCoreApplication::setApplicationName("TimeTracker");
    QCoreApplication::setApplicationVersion("0.1");

    qmlRegisterType<ServiceProvider::QmlWrapper>("PluginManager", 1, 0, "PluginManager");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

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
