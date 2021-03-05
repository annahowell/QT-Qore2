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


class RemoteControl : public QMainWindow
{
    Q_OBJECT

public:
    RemoteControl();
    RemoteControl(Connection *connection);
    void setShortcuts();

    signals:
        void clicked(const QString &text);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Connection *m_connection;
    QTabWidget *tabs;
    QGridLayout *grid, *quitGrid;
    QList<QPushButton*> buttons;
    QSettings *settings;
    QLabel *confirmMsg;
    QPushButton *cancelButton, *quitButton;
    QPushButton *previous, *rewind,   *stop,       *playPause, *fastForward, *next,
                *menu,     *context,  *info,       *back,
                *up,       *down,     *left,       *right,
                *enter,    *volumeUp, *volumeLogo, *volumeDown;
    QSignalMapper  *signalMapper;

    void createWidgets();
    void setUpLayout();
    QWidget *handleQuit();


private slots:
    void handleButton(int buttonCode);
};

#endif // REMOTECONTROL_H
