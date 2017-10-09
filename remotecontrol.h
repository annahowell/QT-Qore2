#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QtWidgets>

#include "connection.h"



class RemoteControl : public QWidget
{
    Q_OBJECT

public:
    RemoteControl();
    void setShortcuts();


private:
    QGridLayout *grid;
    Connection *connection;
    QList<QPushButton*> remote_buttons;
    QPushButton *up, *down, *left, *right, *enter, *back, *volumeUp, \
                *volumeLogo, *volumeDown, *stop, *pause, *play, \
                *previous, *rewind, *fastForward, *next, *showOsd;
    QSignalMapper* signalMapper;
    QLineEdit *sendText;
    QSettings s;

    void createWidgets();
    void setUpLayout();

private slots:
    void handleButton(int buttonCode);
};



#endif // REMOTECONTROL_H
