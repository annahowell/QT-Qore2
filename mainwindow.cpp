#include "mainwindow.h"

MainWindow::MainWindow(RemoteControl *remoteControl, Settings *settings, QWidget *quit)
    : m_remoteControl(remoteControl), m_settings(settings), m_quit(quit)
{
    tabs = new QTabWidget(this);
    tabs->setFixedSize(490, 154);

    tabs->addTab(m_remoteControl, QString::fromUtf8("Remote"));
    tabs->addTab(m_settings, QString::fromUtf8("Settings"));
    tabs->addTab(m_quit, QString::fromUtf8("Quit"));

    setWindowTitle(QString::fromUtf8("Qore2"));
    setFixedSize(490, 154);

    show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    this->destroy();
}

void MainWindow::setTab(int index)
{
    tabs->setCurrentIndex(index);
}
