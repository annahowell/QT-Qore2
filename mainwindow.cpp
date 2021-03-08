#include "mainwindow.h"

MainWindow::MainWindow(bool debug, RemoteControl *remoteControl, Settings *settings, QWidget *quit)
    : m_debug(debug), m_remoteControl(remoteControl), m_settings(settings), m_quit(quit)
{
    if (m_debug) {qDebug() << "Opening main window";}

    setWindowTitle(QString::fromUtf8("Qore2"));
    setFixedSize(490, 154);

    tabs = new QTabWidget(this);
    tabs->setFixedSize(490, 154);

    tabs->addTab(m_remoteControl, QString::fromUtf8("Remote"));
    tabs->addTab(m_settings, QString::fromUtf8("Settings"));
    tabs->addTab(m_quit, QString::fromUtf8("Quit"));

    show();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_debug) {qDebug() << "Closing main window";}

    event->ignore();

    this->destroy();
}


void MainWindow::setTab(int index)
{
    if (m_debug) {qDebug() << "Setting main window tab index to" << index;}

    tabs->setCurrentIndex(index);
}
