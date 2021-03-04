#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets>
#include <QHotkey>
#include "connection.h"

class Settings : public QWidget
{
    Q_OBJECT

public:
    Settings(Connection *connection, QHotkey *hotkey);

private:
    Connection *m_connection;
    QGridLayout *grid;
    QLabel *ipLabel, *portLabel, *hotKeyLabel;
    QLineEdit *ipEdit, *portEdit;
    QKeySequenceEdit *hotKeyEdit;
    QSettings m_qSettings;
    QPushButton *saveButton, *resetButton;
    QHotkey *m_hotkey;
    QSystemTrayIcon *m_trayIcon;

    void setDefaults(bool doReset);
    void createWidgets();
    void saveSettings();
    void resetSettings();
};

#endif // SETTINGS_H
