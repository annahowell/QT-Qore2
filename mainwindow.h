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
    MainWindow();

public slots:
    void toggleVisibility();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool closing = false;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QGridLayout *quitGrid;
    QLabel *confirmMsg;
    QTabWidget *tabs;
    QPushButton *cancelButton, *quitButton;
    Settings *settings;
    Connection *connection;
    RemoteControl *remoteControl;

    void handleTabChanged(int index);
    QMenu *createMenu();
    QWidget *handleQuit();
};

#endif // MAINWINDOW_H
