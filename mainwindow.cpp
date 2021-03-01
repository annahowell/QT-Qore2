#include "mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    rc = new RemoteControl();
    QTabWidget *tabs = new QTabWidget(this);

    tabs->setFixedSize(490, 160);
    tabs->addTab(rc,"Remote");
    tabs->addTab(new Settings(),"Settings");

    connect(tabs,  &QTabWidget::tabBarClicked, this, [this]{ rc->setShortcuts(); });

    setWindowTitle(QString::fromUtf8("Qore2"));
    setFixedSize(490, 160);
    show();
}


// -------------------------------------------------------------------------


MainWindow::~MainWindow()
{

}
