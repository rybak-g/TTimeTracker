#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

class TrayMenu: public QObject
{
Q_OBJECT

public:
    explicit TrayMenu(QObject *root);
    ~TrayMenu();

signals:
    void hide();
    void show();

public slots:
    void onActivated(QSystemTrayIcon::ActivationReason);

private:
    void toggleProgramHidden();

protected:
    QMenu m_menu;
    QSystemTrayIcon m_trayIcon;
    QAction * m_minimizeAction;
    QAction * m_closeAction;
    QAction * m_restoreAction;
    bool m_programHidden;
};

#endif // TRAYMENU_H
