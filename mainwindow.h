#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QCloseEvent>
#include <QHotkey>
#include "settings.h"
#include "connection.h"
#include "remotecontrol.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(RemoteControl *remoteControl, Settings *settings);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    RemoteControl *m_remoteControl;
    Settings      *m_settings;

    void handleTabChanged(int index);
};

#endif // MAINWINDOW_H
