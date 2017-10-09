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
    QLabel *ipLabel, *portLabel, *usernameLabel, *passwordLabel, *upLabel,
           *downLabel, *leftLabel, *rightLabel, *enterLabel, *backLabel, \
           *volumeDownLabel, *volumeUpLabel, *stopLabel, *pauseLabel, \
           *previousLabel, *rewindLabel, *fastForwardLabel, *nextLabel, *showOsdLabel;

    QLineEdit *ipEdit, *portEdit, *usernameEdit, *passwordEdit, *upEdit, \
              *downEdit, *leftEdit, *rightEdit, *enterEdit, *backEdit, \
              *volumeDownEdit, *volumeUpEdit, *stopEdit, *pauseEdit, *previousEdit, \
              *rewindEdit, *fastForwardEdit, *nextEdit, *showOsdEdit;
    QSettings s;
    QPushButton *saveButton, *resetButton;

    void setDefaults(bool doReset);
    void createWidgets();
    void customiseWidgets();
    void setUpLayout();
    void saveSettings();
    void resetSettings();
    void updateGui();
};

#endif // SETTINGS_H
