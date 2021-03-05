#include "trayapp.h"

TrayApp::TrayApp()
{
    trayIcon = new QSystemTrayIcon();

    // Create and setup the tray icon and intercept attemps to close the
    // app so we can minimise instead
    QIcon appIcon = QIcon(":/icons/tray-icon-white.svg");
    trayIcon->setIcon(appIcon);
    QApplication::setWindowIcon(appIcon);
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayApp::toggleVisibility);

    // Create an empty global hotkey to handle opening and closing, the
    // Settings class will actually set the shortcut
    QHotkey *hotkey = new QHotkey();
    connect(hotkey, &QHotkey::activated, this, &TrayApp::toggleVisibility);


    // Setup the basic components of the app
    connection    = new Connection(true);
    settings      = new Settings(connection, hotkey);
}


void TrayApp::toggleVisibility()
{
    if (opened){
        opened = false;

        remoteControl->close();
    } else {
        opened = true;

        remoteControl = new RemoteControl(connection);


        remoteControl->activateWindow();
        remoteControl->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

        remoteControl->show();
        remoteControl->setFocus();
    }
}
