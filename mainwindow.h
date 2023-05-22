#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QCloseEvent>
#include <QHotkey>
#include "connection.h"
#include "remotecontrol.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(bool debug, RemoteControl *remoteControl);
    void addTabWithText(QString text);

signals:
     void tabIndexChangedSignal(int currentIndex);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool           m_debug;
    RemoteControl *m_remoteControl;
    QTabWidget    *tabWidget;

private slots:
    void saveTabIndexToDisk();
};

#endif // MAINWINDOW_H
