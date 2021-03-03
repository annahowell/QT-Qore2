#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QSettings>
#include <QCloseEvent>
#include "remotecontrol.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool closing;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QGridLayout *quitGrid;
    QLabel *confirmMsg;
    QTabWidget *tabs;
    QPushButton *cancelButton, *quitButton;
    RemoteControl *remoteControl;

    void handleTabChanged(int index);
    QMenu *createMenu();
    QWidget *handleQuit();
};

#endif // MAINWINDOW_H
