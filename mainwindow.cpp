#include "mainwindow.h"

MainWindow::MainWindow(bool debug, RemoteControl *remoteControl)
    : m_debug(debug), m_remoteControl(remoteControl)
{    
    if (m_debug) {
        qDebug() << "Qore2: Running MainWindow::MainWindow()";
    }

    setWindowTitle(QString::fromUtf8("Qore2"));
    setFixedSize(490, 154);

    tabWidget = new QTabWidget(this);
    tabWidget->setFixedSize(490, 154);

    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::saveTabIndexToDisk);

    show();
}


void MainWindow::addTabWithText(QString text)
{
    tabWidget->addTab(m_remoteControl, text);
}


void MainWindow::saveTabIndexToDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running MainWindow:saveTabIndexToDisk() and setting tabIndex to"<<tabWidget->currentIndex();
    }

    emit tabIndexChangedSignal(tabWidget->currentIndex());
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_debug) {
        qDebug() << "Qore2: Running MainWindow::closeEvent()";
    }

    event->ignore();

    this->hide();

    this->destroy();
}

