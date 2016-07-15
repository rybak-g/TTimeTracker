
#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QTime>
#include <QException>

#include <exception>
#include <iostream>

#include "TrayMenu.h"
#include "Phabricator.h"

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

    QCoreApplication::setOrganizationName("TaskTimeTracker");
    QCoreApplication::setApplicationName("TaskTimeTracker");
    QCoreApplication::setApplicationVersion("0.1");

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Providers::Phabricator::ServiceProvider>("Phabricator", 1, 0, "Phabricator");

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
