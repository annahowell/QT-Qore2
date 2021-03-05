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
}
