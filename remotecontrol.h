#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QtWidgets>
#include <QHotkey>
#include <QShortcut>
#include "connection.h"

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
    void onTextMessageReceived(const QString &frame);
    void cancelSendText();
};

#endif // REMOTECONTROL_H
