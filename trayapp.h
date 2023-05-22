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

#define BLACK_ICON ":/icons/tray-icon-black.svg"
#define WHITE_ICON ":/icons/tray-icon-white.svg"

class TrayApp : public QObject
{
    Q_OBJECT

public:
    TrayApp();
    bool getDebug();

private:
    const int KODI_COUNT = 3;
    const bool USE_LIGHT_ICON_DEFAULT_VALUE = false;

    bool             useLightIcon = USE_LIGHT_ICON_DEFAULT_VALUE,
                     settingsOpened;
    int              currentTabIndex;
    Settings        *settings;
    Connection      *connection;
    RemoteControl   *remoteControl;
    MainWindow      *mainWindow;


public slots:
    void toggleIconTheme();

private slots:
    void toggleVisibility();
    void showPreferences();
    void handleTabIndexChangedSlot(int currentTabIndex);
    void handlenicknameChangedSlot();
};


#endif // TRAYAPP_H
