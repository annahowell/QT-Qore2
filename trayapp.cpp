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
    QHotkey *hotkey = new QHotkey(QKeySequence("ctrl+Q"));
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

        // Drawer is good, opens to another screen and focuses etc with raise() with border
        // tooltip is good, ooens to another screen and focuses etc with raise no border

        remoteControl->setWindowFlags(Qt::Drawer | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

        remoteControl->show();
        remoteControl->setFocus();
        remoteControl->activateWindow();
        remoteControl->raise();
    }
}
