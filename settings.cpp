#include "settings.h"

Settings::Settings(Connection *connection) : m_connection(connection)
{
    setDefaults(false);
    createWidgets();
}


void Settings::setDefaults(bool doReset)
{
    if (!settings.contains("ip")     || doReset) {settings.setValue("ip",    "192.168.9.201");}
    if (!settings.contains("port")   || doReset) {settings.setValue("port",  "9090");}
    if (!settings.contains("hotKey") || doReset) {settings.setValue("hotKey", QKeySequence(Qt::ShiftModifier + Qt::Key_1));}
}


void Settings::createWidgets()
{
    grid = new QGridLayout;

    ipLabel     = new QLabel(tr("IP"));
    portLabel   = new QLabel(tr("Port"));
    hotKeyLabel = new QLabel(tr("Hotkey"));
    ipEdit      = new QLineEdit(settings.value("ip").toString());
    portEdit    = new QLineEdit(settings.value("port").toString());
    hotKeyEdit  = new QKeySequenceEdit(settings.value("hotKey").toString());

    ipEdit->setToolTip(QString("Set the IP address of the computer running Kodi"));
    portEdit->setToolTip(QString("Set the websocket port. Kodi uses 9090 by default"));
    hotKeyEdit->setToolTip(QString("Set the global hotkey for showing and hiding Qore2"));

    resetButton = new QPushButton("Defaults");
    saveButton  = new QPushButton("Save Settings");

    ipLabel->setAlignment  (Qt::AlignRight | Qt::AlignVCenter);
    portLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    hotKeyLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    grid->addWidget(ipLabel,     0, 0);
    grid->addWidget(ipEdit,      0, 1);

    grid->addWidget(hotKeyLabel, 0, 2);
    grid->addWidget(hotKeyEdit,  0, 3);

    grid->addWidget(portLabel,   1, 0);
    grid->addWidget(portEdit,    1, 1);

    grid->addWidget(resetButton, 3, 2);
    grid->addWidget(saveButton,  3, 3);

    setLayout(grid);

    connect(resetButton, &QPushButton::pressed, this, [this]{ resetSettings(); });
    connect(saveButton,  &QPushButton::pressed, this, [this]{ saveSettings();  });
}

void Settings::saveSettings()
{
    settings.setValue("ip",     ipEdit->displayText());
    settings.setValue("port",   portEdit->displayText());
    settings.setValue("hotKey", hotKeyEdit->keySequence());

    m_connection->constructUrl();
}


void Settings::resetSettings()
{
    setDefaults(true);

    ipEdit->setText(settings.value("ip").toString());
    portEdit->setText(settings.value("port").toString());
    hotKeyEdit->setKeySequence(QKeySequence(Qt::ShiftModifier + Qt::Key_1));
}
