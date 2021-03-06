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

public slots:
    void toggleVisibility();

protected:

private:
    Settings        *settings;
    Connection      *connection;
    RemoteControl   *remoteControl;
    MainWindow      *mainWindow;
    bool             opened;

    QWidget* handleQuit();
};


#endif // TRAYAPP_H
