#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QtWidgets>
#include <QHotkey>
#include <QShortcut>
#include "connection.h"

#define PREVIOUS         1
#define BIG_STEP_BACK    2
#define STEP_BACK        3
#define REWIND           4
#define STOP             5
#define PLAY_PAUSE       6
#define FAST_FORWARD     7
#define STEP_FORWARD     8
#define BIG_STEP_FORWARD 9
#define NEXT             10
#define MENU             11
#define CONTEXT          12
#define INFO             13
#define BACK             14
#define UP               15
#define DOWN             16
#define LEFT             17
#define RIGHT            18
#define ENTER            19
#define VOLUME_UP        20
#define VOLUME_DOWN      21
#define MUTE             22


class RemoteControl : public QWidget
{
    Q_OBJECT

public:
    RemoteControl(bool debug, Connection *connection);
    bool getTextInputShouldBeOpen();
    void openTextInput(bool updateShouldBeOpenBool);
    void closeTextInput(bool updateShouldBeOpenBool);
    void sendText();

private:
    bool                 m_debug, textInputShouldBeOpen;
    Connection          *m_connection;
    QList<QPushButton*>  buttons;
    QDialog             *textInputDialog;
    QLineEdit           *textInput;
    QPushButton         *cancelButton, *quitButton;
    QPushButton         *previous, *rewind,   *stop,       *playPause, *fastForward, *next,
                        *menu,     *context,  *info,       *back,
                        *up,       *down,     *left,       *right,
                        *enter,    *volumeUp, *volumeLogo, *volumeDown;

    void createWidgets();
    void setShortcutsAndBindings();
    void setUpLayout();
    void setUpTextInput();

private slots:
    void handleRemote(int code);
    void onTextMessageReceived(const QString &frame);
    void cancelSendText();
};

#endif // REMOTECONTROL_H
