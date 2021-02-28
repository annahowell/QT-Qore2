#include "settings.h"


Settings::Settings()
{
    setDefaults(false);
    createWidgets();
    customiseWidgets();
    setUpLayout();
}


// -------------------------------------------------------------------------

// Check to see if values already exist in config and if they don't or if true is passed to the function generate defaults
//                                                          Name           Default
void Settings::setDefaults(bool doReset)
{
    if (!s.contains("ip")          || doReset) {s.setValue("ip",          "192.168.1.200");}
    if (!s.contains("port")        || doReset) {s.setValue("port",        "8080");}
    if (!s.contains("username")    || doReset) {s.setValue("username",    "kodi");}
    if (!s.contains("password")    || doReset) {s.setValue("password",    "kodi");}
}


// -------------------------------------------------------------------------


void Settings::createWidgets()
{
    grid = new QGridLayout;
    setLayout(grid);

    ipLabel = new QLabel(tr("IP "));
    ipEdit = new QLineEdit(s.value("ip").toString());

    portLabel = new QLabel(tr("Port "));
    portEdit = new QLineEdit(s.value("port").toString());

    resetButton = new QPushButton("Defaults");
    saveButton = new QPushButton("Save Settings");

    connect(resetButton, &QPushButton::clicked, this, [this]{ resetSettings(); });
    connect(saveButton,  &QPushButton::clicked, this, [this]{ saveSettings();  });
}


// -------------------------------------------------------------------------


void Settings::customiseWidgets()
{
    ipLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    portLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    portLabel->setContentsMargins(0, 0, 0, 15);
    portEdit->setContentsMargins(0, 0, 0, 15);
}


// -------------------------------------------------------------------------


void Settings::setUpLayout()
{
    grid->addWidget(ipLabel, 0, 0);
    grid->addWidget(ipEdit, 0, 1);
    grid->addWidget(portLabel, 1, 0);
    grid->addWidget(portEdit, 1, 1);

    grid->addWidget(resetButton, 10, 2);
    grid->addWidget(saveButton, 10, 3);
}


// -------------------------------------------------------------------------


void Settings::saveSettings()
{
    s.setValue("ip", ipEdit->displayText());
    s.setValue("port", portEdit->displayText());
}


// -------------------------------------------------------------------------


void Settings::resetSettings()
{
    setDefaults(true);
    updateGui();
}


// -------------------------------------------------------------------------


void Settings::updateGui()
{
    ipEdit->setText(s.value("ip").toString());
    portEdit->setText(s.value("port").toString());
}
