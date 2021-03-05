#ifndef TRAYAPP_H
#define TRAYAPP_H

#include <QApplication>
#include <QIcon>
#include <QHotkey>
#include <QSystemTrayIcon>

class TrayApp : public QObject
{
    Q_OBJECT

public:
    TrayApp();

private:
    QSystemTrayIcon *trayIcon;
};

#endif // TRAYAPP_H
