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
    w.show();

    Connection client(QUrl(QStringLiteral("ws://127.0.0.1:9090")), true);
    //QObject::connect(&client, &Connection::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
