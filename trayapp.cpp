#include "trayapp.h"

TrayApp::TrayApp()
{
    // When the app starts, we don't show it
    opened = false;

    // Create empty hotkey and system icon, Settings will actually set the shortcut and icon
    QHotkey *hotkey = new QHotkey();
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();

    connect(hotkey, &QHotkey::activated, this, &TrayApp::toggleVisibility);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayApp::toggleVisibility);

    connection = new Connection(true);
    settings = new Settings(connection, hotkey, trayIcon);
    remoteControl = new RemoteControl(connection);

    QMenu menu;
    menu.addAction("Exit",this,SLOT(close()));

    trayIcon->setContextMenu(&menu);
    //connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(Actived(QSystemTrayIcon::ActivationReason)));
}


void TrayApp::toggleVisibility()
{
    if (opened){
        opened = false;

        mainWindow->close();
    } else {
        opened = true;

        mainWindow = new MainWindow(remoteControl, settings);

        // Drawer is good, opens to another screen and focuses etc with raise() but has a border
        // tooltip is good, ooens to another screen and focuses etc with raise() and has no border
        mainWindow->setWindowFlags(Qt::ToolTip | Qt::WindowStaysOnTopHint);

        mainWindow->show();
        mainWindow->setFocus();
        mainWindow->activateWindow();
        mainWindow->raise();
    }
}
