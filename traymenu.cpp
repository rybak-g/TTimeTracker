#include <QApplication>
#include "traymenu.h"

TrayMenu::TrayMenu(QObject * root) : QObject(root),  m_menu(), m_trayIcon(root), m_programHidden(false)
{
    this->m_minimizeAction = new QAction(QObject::tr("Minimize"), root);
    this->m_restoreAction = new QAction(QObject::tr("Restore"), root);
    this->m_closeAction = new QAction(QObject::tr("Quit"), root);
    root->connect(m_minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
    root->connect(m_restoreAction, SIGNAL(triggered()), root, SLOT(showNormal()));
    root->connect(m_closeAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    this->m_menu.addAction(m_minimizeAction);
    this->m_menu.addAction(m_restoreAction);
    this->m_menu.addSeparator();
    this->m_menu.addAction(m_closeAction);

    m_trayIcon.setContextMenu(&m_menu);
    m_trayIcon.setIcon(QIcon(":/icon/tray_icon.png"));
    m_trayIcon.connect(&m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
    connect(this, SIGNAL(show()), root, SLOT(showNormal()));
    connect(this, SIGNAL(hide()), root, SLOT(hide()));
    m_trayIcon.show();
}

void TrayMenu::toggleProgramHidden() {
    m_programHidden = !m_programHidden;
    if (m_programHidden) {
        emit hide();
    } else {
        emit show();
    }

}

void TrayMenu::onActivated(QSystemTrayIcon::ActivationReason activationReason) {
    switch (activationReason) {
    case QSystemTrayIcon::Trigger: toggleProgramHidden(); break;
    case QSystemTrayIcon::DoubleClick: toggleProgramHidden(); break;
    default:
        break;
    }
}
