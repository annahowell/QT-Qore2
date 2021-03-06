#include "trayapp.h"

TrayApp::TrayApp()
{
    // When the app starts, we don't show it
    opened = false;

    // Create empty hotkey and system icon, Settings will actually set the shortcut and icon
    QHotkey *hotkey = new QHotkey();
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
    QMenu* trayMenu = new QMenu();;

    //connect(hotkey, &QHotkey::activated, this, &TrayApp::toggleVisibility);

    connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason) {
        switch(reason) {
            case QSystemTrayIcon::Context:
                qDebug() << "rightClick";
                trayMenu->setDisabled(false);
                trayMenu->show();

            default:
                toggleVisibility();
        }
    });


    connection = new Connection(true);
    settings = new Settings(connection, hotkey, trayIcon);
    remoteControl = new RemoteControl(connection);

    trayMenu->setDisabled(true);

    trayMenu->addAction("&Show");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->installEventFilter(this);

    //connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayApp::toggleVisibility);

    //connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(Actived(QSystemTrayIcon::ActivationReason)));
}


bool TrayApp::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << "sdfssd";


//    if (obj == textEdit) {
//        if (event->type() == QEvent::KeyPress) {
//            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//            qDebug() << "Ate key press" << keyEvent->key();
//            return true;
//        } else {
//            return false;
//        }
//    } else {
//        // pass the event on to the parent class
//        return TrayApp::eventFilter(obj, event);
//    }
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
