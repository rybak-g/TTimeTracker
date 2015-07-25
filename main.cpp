#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QQmlApplicationEngine>

static void initTrayMenu(QQmlApplicationEngine & engine) {
    QObject *root = 0;
    if (engine.rootObjects().size() > 0)
    {
        root = engine.rootObjects().at(0);

        QAction *minimizeAction = new QAction(QObject::tr("Minimize"), root);
        QAction *restoreAction = new QAction(QObject::tr("Restore"), root);
        QAction *quitAction = new QAction(QObject::tr("Quit"), root);
        root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
        root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(showNormal()));
        root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        QMenu *trayIconMenu = new QMenu();
        trayIconMenu->addAction(minimizeAction);
        trayIconMenu->addAction(restoreAction);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(quitAction);

        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon(":/icon/tray_icon.png"));
        trayIcon->connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), root, SLOT(showNormal()));
        trayIcon->show();
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    initTrayMenu(engine);

    return app.exec();
}
