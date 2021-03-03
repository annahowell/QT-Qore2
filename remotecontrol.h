#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QtWidgets>
#include "connection.h"

#define PREVIOUS     1
#define REWIND       2
#define STOP         3
#define PLAY_PAUSE   4
#define FAST_FORWARD 5
#define NEXT         6
#define MENU         7
#define CONTEXT      8
#define INFO         9
#define BACK         10
#define UP           11
#define DOWN         12
#define LEFT         13
#define RIGHT        14
#define ENTER        15
#define VOLUME_UP    16
#define VOLUME_DOWN  17


class RemoteControl : public QWidget
{
    Q_OBJECT

public:
    RemoteControl();
    void setShortcuts();

private:
    QGridLayout *grid;
    QList<QPushButton*> buttons;
    QPushButton *previous, *rewind,   *stop,       *playPause, *fastForward, *next,
                *menu,     *context,  *info,       *back,
                *up,       *down,     *left,       *right,
                *enter,    *volumeUp, *volumeLogo, *volumeDown;
    QSignalMapper  *signalMapper;
    QSettings *settings;
    Connection *connection;

    void createWidgets();
    void setUpLayout();

private slots:
    void handleButton(int buttonCode);
};

#endif // REMOTECONTROL_H
