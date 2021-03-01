#include "settings.h"

Settings::Settings()
{
    setDefaults(false);
    createWidgets();
    setUpLayout();
}


void Settings::setDefaults(bool doReset)
{
    if (!s.contains("ip")   || doReset) {s.setValue("ip",   "192.168.9.201");}
    if (!s.contains("port") || doReset) {s.setValue("port", "8080");}
}


void Settings::createWidgets()
{
    grid = new QGridLayout;
    setLayout(grid);

    ipLabel = new QLabel(tr("IP"));
    ipEdit  = new QLineEdit(s.value("ip").toString());

    portLabel = new QLabel(tr("Port"));
    portEdit  = new QLineEdit(s.value("port").toString());

    resetButton = new QPushButton("Defaults");
    saveButton  = new QPushButton("Save Settings");

    ipLabel->setAlignment  (Qt::AlignRight | Qt::AlignVCenter);
    portLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(resetButton, &QPushButton::clicked, this, [this]{ resetSettings(); });
    connect(saveButton,  &QPushButton::clicked, this, [this]{ saveSettings();  });
}


void Settings::setUpLayout()
{
    grid->addWidget(ipLabel,     0, 0);
    grid->addWidget(ipEdit,      0, 1);

    grid->addWidget(portLabel,   1, 0);
    grid->addWidget(portEdit,    1, 1);

    grid->addWidget(resetButton, 2, 2);
    grid->addWidget(saveButton,  2, 3);
}


void Settings::saveSettings()
{
    s.setValue("ip",   ipEdit->displayText());
    s.setValue("port", portEdit->displayText());
}


void Settings::resetSettings()
{
    setDefaults(true);
    updateGui();
}


void Settings::updateGui()
{
    ipEdit->setText(s.value("ip").toString());
    portEdit->setText(s.value("port").toString());
}
