#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets>
#include "connection.h"

class Settings : public QWidget
{
    Q_OBJECT

public:
    Settings(Connection *connection);

private:
    Connection *m_connection;
    QGridLayout *grid;
    QLabel *ipLabel, *portLabel, *hotKeyLabel;
    QLineEdit *ipEdit, *portEdit;
    QKeySequenceEdit *hotKeyEdit;
    QSettings settings;
    QPushButton *saveButton, *resetButton;

    void setDefaults(bool doReset);
    void createWidgets();
    void saveSettings();
    void resetSettings();
};

#endif // SETTINGS_H
