#ifndef TRAYAPP_H
#define TRAYAPP_H

#include <QApplication>
#include <QIcon>
#include <QHotkey>
#include <QSystemTrayIcon>
#include "settings.h"
#include "connection.h"
#include "remotecontrol.h"

class TrayApp : public QObject
{
    Q_OBJECT

public:
    TrayApp();

public slots:
    void toggleVisibility();

private:
    QSystemTrayIcon *trayIcon;
    Settings *settings;
    Connection *connection;
    RemoteControl *remoteControl;
    bool opened = false;
};

#endif // TRAYAPP_H
