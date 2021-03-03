#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("qore2-kodi-remote");
    QApplication::setApplicationName("qore2-kodi-remote");

    MainWindow w;
    w.setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    w.show();

    return a.exec();
}
