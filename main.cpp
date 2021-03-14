#include <QApplication>
#include <QSettings>
#include "mainwindow.h"
#include "trayapp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("Qore2-Anna-Howell");
    QApplication::setApplicationName("Qore2");

    a.setWindowIcon(QIcon("Qore2.ico"));

    TrayApp ta;

    return a.exec();
}
