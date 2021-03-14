#include "trayapp.h"

TrayApp::TrayApp()
{
    debug = false;

    // When the app starts we don't show the remote; the user has to either click the menu icon or use the global hotkey
    opened = false;

    // Create empty hotkey and system icon, Settings will actually set the shortcut and icon
    QHotkey *hotkey = new QHotkey();
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();

    connect(hotkey, &QHotkey::activated, this, &TrayApp::toggleVisibility);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayApp::toggleVisibility);

    connection    = new Connection(debug);
    settings      = new Settings(debug, connection, hotkey, trayIcon);
    remoteControl = new RemoteControl(debug, connection);
}


void TrayApp::toggleVisibility()
{
    if (opened) {
        opened = false;

        if (remoteControl->getTextInputShouldBeOpen()) {
            remoteControl->closeTextInput(false);
        }

        mainWindow->close();
    } else {
        opened = true;

        mainWindow = new MainWindow(debug, remoteControl, settings, quitTabWidget());

        mainWindow->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

        mainWindow->show();
        mainWindow->setFocus();
        mainWindow->activateWindow();
        mainWindow->raise();

        if (remoteControl->getTextInputShouldBeOpen()) {
            remoteControl->openTextInput(false); // False we're not done, so don't alter the textInputShouldBeOpen bool
        }
    }
}


QWidget* TrayApp::quitTabWidget()
{
    QWidget     *quitWidget   = new QWidget();
    QGridLayout *grid         = new QGridLayout();
    QLabel      *confirmMsg   = new QLabel(tr("Are you sure you wish to quit?"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    QPushButton *quitButton   = new QPushButton(tr("Ok"));

    grid->setHorizontalSpacing(4);
    grid->setVerticalSpacing(8);

    grid->setColumnMinimumWidth(0, 50);
    grid->setColumnMinimumWidth(2, 20);
    grid->setColumnMinimumWidth(4, 50);

    cancelButton->setFixedWidth(100);
    quitButton->setFixedWidth(100);

    grid->addWidget(confirmMsg,   0, 1, 1, 3, Qt::AlignCenter); //row col rowSpan colSpan
    grid->addWidget(cancelButton, 1, 1, Qt::AlignCenter);
    grid->addWidget(quitButton,   1, 3, Qt::AlignCenter);

    connect(quitButton, &QPushButton::clicked, this, &QApplication::quit);
    connect(cancelButton, &QPushButton::clicked, this, [this]{ mainWindow->setTab(0); });

    quitWidget->setLayout(grid);

    return quitWidget;
}
