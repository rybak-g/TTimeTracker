#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTime>
#include <QException>

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
        break;
    }
    std::cerr << localMsg.data();
    if (context.file) {
        std::cerr << " (" << (context.file ? context.file : "no_file")
                  << ":" << context.line
                  << ", " << (context.function ? context.function : "no_function") << ")";
    }
    std::cerr << std::endl;
    if (type == QtFatalMsg) {
        abort();
    }
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
        TrayMenu tm(engine.rootObjects().at(0));
        Q_UNUSED(tm);
        return app.exec();
    } catch (const QException & e) {
        qFatal(e.what());
    } catch (const std::exception & e) {
        qFatal(e.what());
    } catch (...) {
        qFatal("An unexpected error occured, exiting");
    }
}
