#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QtWidgets>
#include <QHotkey>
#include <QShortcut>
#include "connection.h"

#define PREVIOUS         1
#define BIG_STEP_BACK    2
#define REWIND           3
#define STOP             4
#define PLAY_PAUSE       5
#define FAST_FORWARD     6
#define BIG_STEP_FORWARD 7
#define NEXT             8
#define MENU             9
#define CONTEXT          10
#define INFO             11
#define BACK             12
#define UP               13
#define DOWN             14
#define LEFT             15
#define RIGHT            16
#define ENTER            17
#define VOLUME_UP        18
#define VOLUME_DOWN      19


class RemoteControl : public QWidget
{
    Q_OBJECT

public:
    RemoteControl(Connection *connection);

private:
    Connection          *m_connection;
    QSignalMapper       *signalMapper;
    QList<QPushButton*>  buttons;
    QPushButton         *cancelButton, *quitButton;
    QPushButton         *previous, *rewind,   *stop,       *playPause, *fastForward, *next,
                        *menu,     *context,  *info,       *back,
                        *up,       *down,     *left,       *right,
                        *enter,    *volumeUp, *volumeLogo, *volumeDown;

    void createWidgets();
    void setShortcuts();
    void setUpLayout();

private slots:
    void handleRemote(int code);
};

#endif // REMOTECONTROL_H
