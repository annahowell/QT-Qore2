#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets>
#include <QHotkey>
#include "connection.h"

#define BLACK_ICON ":/icons/tray-icon-black.svg"
#define WHITE_ICON ":/icons/tray-icon-white.svg"

class Settings : public QWidget
{
    Q_OBJECT

public:
    Settings(bool debug, Connection *connection, QHotkey *hotkey, QSystemTrayIcon *trayIcon);

private slots:
    void toggleMenuIconColor();
    void resetSettings();
    void saveSettings();

private:
    bool              darkTheme, m_debug;
    Connection       *m_connection;
    QLabel           *ipLabel, *portLabel, *hotKeyLabel;
    QLineEdit        *ipEdit, *portEdit;
    QKeySequenceEdit *hotKeyEdit;
    QSettings        *settings;
    QPushButton      *toggleButton, *saveButton, *resetButton;
    QHotkey          *m_hotkey;
    QSystemTrayIcon  *m_trayIcon;

    void setDefaults(bool doReset);
    void setupFromDisk();
    void createWidgets();
    QString getUrl();
};

#endif // SETTINGS_H
