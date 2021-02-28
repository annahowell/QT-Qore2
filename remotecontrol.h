#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QtWidgets>
#include "connection.h"

#define UP           0
#define DOWN         1
#define LEFT         2
#define RIGHT        3
#define ENTER        4
#define VOLUME_UP    5
#define VOLUME_DOWN  6
#define PREVIOUS     7
#define STOP         8
#define PLAY_PAUSE   9
#define NEXT         10
#define HOME         11
#define INFO         12
#define MENU         13
#define BACK         14

class RemoteControl : public QWidget
{
    Q_OBJECT

public:
    RemoteControl();
    void setShortcuts();

private:
    QGridLayout *grid;
    Connection *connection;
    QList<QPushButton*> buttons;
    QPushButton *up,       *down,       *left,       *right, *enter, \
                *volumeUp, *volumeLogo, *volumeDown,                 \
                *previous, *stop,       *playPause,  *next,          \
                *home,     *info,       *menu,       *back;
    QSignalMapper* signalMapper;
    QLineEdit *sendText;
    QSettings settings;

    void createWidgets();
    void setUpLayout();

private slots:
    void handleButton(int buttonCode);
};



#endif // REMOTECONTROL_H
