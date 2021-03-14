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
    MainWindow(bool debug, RemoteControl *remoteControl, Settings *settings, QWidget *quit);
    void setTab(int index);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool           m_debug;
    RemoteControl *m_remoteControl;
    Settings      *m_settings;
    QWidget       *m_quit;
    QTabWidget    *tabs;
};

#endif // MAINWINDOW_H
