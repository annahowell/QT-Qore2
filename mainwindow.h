#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QSettings>
#include "remotecontrol.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSettings s;
    RemoteControl *rc;
    void aaa();
};

#endif // MAINWINDOW_H
