#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), trayIcon(new QSystemTrayIcon(this))
{
    QIcon appIcon = QIcon(":/icons/tray-icon-white.svg");
    this->trayIcon->setIcon(appIcon);
    this->setWindowIcon(appIcon);
    this->trayIcon->show();

    QAction *exitAction = new QAction(tr("&Exit"), this);

    connect(exitAction, &QAction::triggered, [this]() {
        closing = true;
        close();
    });

    // Interaction
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);

    connection    = new Connection(true);
    settings      = new Settings(connection);
    remoteControl = new RemoteControl(connection);
    tabs          = new QTabWidget(this);

    tabs->setFixedSize(490, 154);
    tabs->addTab(remoteControl, QString::fromUtf8("Remote"));
    tabs->addTab(settings, QString::fromUtf8("Settings"));
    tabs->addTab(MainWindow::handleQuit(), QString::fromUtf8("Quit"));

    setWindowTitle(QString::fromUtf8("Qore2"));
    setFixedSize(490, 154);
    show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (closing) {
        event->accept();
    } else {
        this->hide();
        event->ignore();
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (isVisible()) {
            hide();
        } else {
            show();
            setFocus();
            activateWindow();
        }
    }
}

QWidget* MainWindow::handleQuit()
{
    QWidget *quitWidget = new QWidget();
    quitGrid            = new QGridLayout();

    confirmMsg   = new QLabel(tr("Are you sure you wish to quit?"));
    cancelButton = new QPushButton("Cancel");
    quitButton   = new QPushButton("Ok");

    cancelButton->setFixedWidth(100);
    quitButton->setFixedWidth(100);

    quitGrid->setHorizontalSpacing(4);
    quitGrid->setVerticalSpacing(8);

    quitGrid->setColumnMinimumWidth(0, 50);
    quitGrid->setColumnMinimumWidth(2, 20);
    quitGrid->setColumnMinimumWidth(4, 50);

    quitGrid->addWidget(confirmMsg,   0, 1, 1, 3, Qt::AlignCenter); //row col rowSpan colSpan
    quitGrid->addWidget(cancelButton, 1, 1, 1, 1, Qt::AlignCenter);
    quitGrid->addWidget(quitButton,   1, 3, 1, 1, Qt::AlignCenter);

    connect(quitButton,   &QPushButton::clicked, this, &QApplication::quit);
    connect(cancelButton, &QPushButton::clicked, this, [this]{
        tabs->setCurrentIndex(0);
    });

    quitWidget->setLayout(quitGrid);

    return quitWidget;
}
