#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets>

class Settings : public QWidget
{
    Q_OBJECT

public:
    Settings();

private:
    QGridLayout *grid;
    QLabel *ipLabel, *portLabel;

    QLineEdit *ipEdit, *portEdit;
    QSettings s;
    QPushButton *saveButton, *resetButton;

    void setDefaults(bool doReset);
    void createWidgets();
    void setUpLayout();
    void saveSettings();
    void resetSettings();
    void updateGui();
};

#endif // SETTINGS_H
