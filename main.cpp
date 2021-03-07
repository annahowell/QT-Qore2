#include <QApplication>
#include <QSettings>
#include "mainwindow.h"
#include "trayapp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("Anna Howell");
    QApplication::setApplicationName("Qore2 Remote");

    a.setWindowIcon(QIcon(":/icons/tray-icon-black.svg"));

    TrayApp ta;

    return a.exec();
}


// Desktop icon
//  https://icons-for-free.com/Remote+Control-1320568044590850575/
//  https://creativecommons.org/licenses/by-nc-nd/4.0/                  CC BY-NC-ND 4.0

// QHotKey
//  https://github.com/Skycoder42/QHotkey
//  https://github.com/Skycoder42/QHotkey/blob/master/LICENSE           BSD 3

// Tray icon
//  https://iconscout.com/icon/remote-network-signal-range-setting
//  https://www.apache.org/licenses/LICENSE-2.0                         Apache 2.0
