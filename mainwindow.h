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
    MainWindow(RemoteControl *remoteControl, Settings *settings, QWidget *quit);
    void setTab(int index);
    QWidget* handleQuit();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QTabWidget    *tabs;
    RemoteControl *m_remoteControl;
    Settings      *m_settings;
    QWidget       *m_quit;

    void handleTabChanged(int index);
};

#endif // MAINWINDOW_H
