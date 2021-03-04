#include "settings.h"

Settings::Settings(Connection *connection, QHotkey *hotkey) : m_connection(connection), m_hotkey(hotkey)
{
    setDefaults(false);
    createWidgets();
}

void Settings::setDefaults(bool doReset)
{
    if (!m_qSettings.contains("ip")     || doReset) {m_qSettings.setValue("ip",    "192.168.9.201");}
    if (!m_qSettings.contains("port")   || doReset) {m_qSettings.setValue("port",  "9090");}
    if (!m_qSettings.contains("hotkey") || doReset) {m_qSettings.setValue("hotkey", QKeySequence(Qt::ShiftModifier + Qt::Key_1));}

    m_hotkey->setShortcut(QKeySequence::fromString(m_qSettings.value("hotkey").toString()));
    m_hotkey->setRegistered(true);
}

void Settings::createWidgets()
{
    grid = new QGridLayout;

    ipLabel     = new QLabel(tr("IP:"));
    portLabel   = new QLabel(tr("Port:"));
    hotKeyLabel = new QLabel(tr("Hotkey:"));
    ipEdit      = new QLineEdit(m_qSettings.value("ip").toString());
    portEdit    = new QLineEdit(m_qSettings.value("port").toString());
    hotKeyEdit  = new QKeySequenceEdit(m_qSettings.value("hotkey").toString());

    ipEdit->setToolTip(QString("Set the IP address of the computer running Kodi"));
    portEdit->setToolTip(QString("Set the websocket port. Kodi uses 9090 by default"));
    hotKeyEdit->setToolTip(QString("Set the global hotkey for showing and hiding Qore2"));

    resetButton = new QPushButton("Defaults");
    saveButton  = new QPushButton("Save");

    ipLabel->setAlignment  (Qt::AlignRight | Qt::AlignVCenter);
    portLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    hotKeyLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    grid->setColumnMinimumWidth (2, 90);


    grid->addWidget(ipLabel,     0, 0);
    grid->addWidget(ipEdit,      0, 1);

    grid->addWidget(hotKeyLabel, 0, 2);
    grid->addWidget(hotKeyEdit,  0, 3, 1, 2);

    grid->addWidget(portLabel,   1, 0);
    grid->addWidget(portEdit,    1, 1);

    grid->addWidget(resetButton, 3, 3);
    grid->addWidget(saveButton,  3, 4);

    setLayout(grid);

    connect(resetButton, &QPushButton::pressed, this, [this]{ resetSettings(); });
    connect(saveButton,  &QPushButton::pressed, this, [this]{ saveSettings(); });
}

void Settings::saveSettings()
{
    m_qSettings.setValue("ip",     ipEdit->displayText());
    m_qSettings.setValue("port",   portEdit->displayText());
    m_qSettings.setValue("hotkey", hotKeyEdit->keySequence().toString());

    m_connection->constructUrl();

    m_hotkey->setRegistered(false);
    m_hotkey->setShortcut(QKeySequence::fromString(m_qSettings.value("hotkey").toString()));
    m_hotkey->setRegistered(true);
}


void Settings::resetSettings()
{
    setDefaults(true);

    ipEdit->setText(m_qSettings.value("ip").toString());
    portEdit->setText(m_qSettings.value("port").toString());
    hotKeyEdit->setKeySequence(QKeySequence(Qt::ShiftModifier + Qt::Key_1));
}
