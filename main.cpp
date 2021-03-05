#include <QApplication>
#include <QSettings>
#include "mainwindow.h"
#include "trayapp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("qore2-remote");
    QApplication::setApplicationName("qore2-remote");

//    MainWindow w;
//    w.setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
//    w.show();

    RemoteControl rc;
    //TrayApp ta;
    rc.setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);


    return a.exec();
}
