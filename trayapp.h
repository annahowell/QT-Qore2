#ifndef TRAYAPP_H
#define TRAYAPP_H

#include <QApplication>
#include <QIcon>
#include <QHotkey>
#include <QSystemTrayIcon>
#include "settings.h"
#include "connection.h"
#include "remotecontrol.h"
#include "mainwindow.h"

class TrayApp : public QObject
{
    Q_OBJECT
public:
    TrayApp();

private:
    bool           debug, opened;
    Settings      *settings;
    Connection    *connection;
    RemoteControl *remoteControl;
    MainWindow    *mainWindow;

    QWidget *quitTabWidget();

private slots:
    void toggleVisibility();
};


#endif // TRAYAPP_H
