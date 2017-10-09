#include "mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    rc = new RemoteControl();
    QTabWidget *tabs = new QTabWidget(this);

    tabs->setFixedSize(400, 450);
    tabs->addTab(rc,"Remote Control");
    tabs->addTab(new Settings(),"Settings");

    connect(tabs,  &QTabWidget::tabBarClicked, this, [this]{ rc->setShortcuts();  });

    setWindowTitle(QString::fromUtf8("Kodi Remote"));
    resize(400, 450);
    show();
}


// -------------------------------------------------------------------------


MainWindow::~MainWindow()
{

}
