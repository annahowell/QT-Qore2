#include "trayapp.h"

TrayApp::TrayApp()
{
    // When the app starts, we don't show it
    opened = false;

    // Create empty hotkey and system icon, Settings will actually set the shortcut and icon
    QHotkey           *hotkey = new QHotkey();
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();

    connect(hotkey, &QHotkey::activated, this, &TrayApp::toggleVisibility);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayApp::toggleVisibility);

    connection    = new Connection(true);
    settings      = new Settings(connection, hotkey, trayIcon);
    remoteControl = new RemoteControl(connection);
}


void TrayApp::toggleVisibility()
{
    if (opened){
        opened = false;

        mainWindow->close();
    } else {
        opened = true;

        mainWindow = new MainWindow(remoteControl, settings, handleQuit());

        // Drawer is good, opens to another screen and focuses etc with raise() but has a border
        // tooltip is good, ooens to another screen and focuses etc with raise() and has no border
        mainWindow->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

        mainWindow->show();
        mainWindow->setFocus();
        mainWindow->activateWindow();
        mainWindow->raise();
    }
}


QWidget* TrayApp::handleQuit()
{
    QWidget *quitWidget       = new QWidget();
    QGridLayout *grid         = new QGridLayout();
    QLabel *confirmMsg        = new QLabel(tr("Are you sure you wish to quit?"));
    QPushButton *cancelButton = new QPushButton("Cancel");
    QPushButton *quitButton   = new QPushButton("Ok");

    cancelButton->setFixedWidth(100);
    quitButton->setFixedWidth(100);

    grid->setHorizontalSpacing(4);
    grid->setVerticalSpacing(8);

    grid->setColumnMinimumWidth(0, 50);
    grid->setColumnMinimumWidth(2, 20);
    grid->setColumnMinimumWidth(4, 50);

    grid->addWidget(confirmMsg,   0, 1, 1, 3, Qt::AlignCenter); //row col rowSpan colSpan
    grid->addWidget(cancelButton, 1, 1, Qt::AlignCenter);
    grid->addWidget(quitButton,   1, 3, Qt::AlignCenter);

    connect(quitButton,   &QPushButton::clicked, this, &QApplication::quit);
    connect(cancelButton, &QPushButton::clicked, this, [this]{
        mainWindow->setTab(0);
    });

    quitWidget->setLayout(grid);

    return quitWidget;
}
