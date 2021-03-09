#include "settings.h"

Settings::Settings(bool debug, Connection *connection, QHotkey *hotkey, QSystemTrayIcon *trayIcon)
    :  m_debug(debug), m_connection(connection), m_hotkey(hotkey), m_trayIcon(trayIcon)
{
    settings = new QSettings;

    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

    setDefaults(false); // False we're not doing a reset
    setupFromDisk();
    createWidgets();
}


void Settings::setDefaults(bool doReset)
{
    // Set defaults if either they params don't exist or we're reseeting to defaults
    if (!settings->contains("ip") || doReset) {
        settings->setValue("ip",    "192.168.9.201");
    }

    if (!settings->contains("port") || doReset) {
        settings->setValue("port",  "9090");
    }

    if (!settings->contains("hotkey") || doReset) {
        settings->setValue("hotkey", QKeySequence(Qt::ControlModifier + Qt::Key_1));
    }

    if (!settings->contains("darkTheme") || doReset) {
        settings->setValue("darkTheme", false);
    }

    if (doReset) {
        ipEdit->setText(settings->value("ip").toString());
        portEdit->setText(settings->value("port").toString());
        hotKeyEdit->setKeySequence(QKeySequence(Qt::ControlModifier + Qt::Key_1));
    }
}


void Settings::setupFromDisk()
{
    // Set the connection url
    QString url = nullptr;
    QString prefix = "ws://";
    QString ip = settings->value("ip").toString();
    QString seperator = ":";
    QString port = settings->value("port").toString();

    url.reserve(prefix.length() + ip.length() + seperator.length() + port.length());
    url.append(prefix).append(ip).append(seperator).append(port);

    m_connection->setUrl(url);

    // Set the hotkey
    m_hotkey->setRegistered(false);
    m_hotkey->setShortcut(QKeySequence::fromString(settings->value("hotkey").toString()));
    m_hotkey->setRegistered(true);

    // Set the tray icon
    darkTheme = settings->value("darkTheme").toBool();

    m_trayIcon->setIcon(darkTheme ? QIcon(WHITE_ICON) : QIcon(BLACK_ICON));
    m_trayIcon->show();
}


void Settings::createWidgets()
{
    QGridLayout *grid = new QGridLayout;

    ipLabel       = new QLabel(tr("IP:"));
    portLabel     = new QLabel(tr("Port:"));
    hotKeyLabel   = new QLabel(tr("Hotkey:"));
    ipEdit        = new QLineEdit(settings->value("ip").toString());
    portEdit      = new QLineEdit(settings->value("port").toString());
    hotKeyEdit    = new QKeySequenceEdit(settings->value("hotkey").toString());
    toggleButton  = new QPushButton(QString(tr("Toggle Dark Icon")));

    ipEdit->setToolTip(QString(tr("Set the IP address of the computer running Kodi")));
    portEdit->setToolTip(QString(tr("Set the websocket port. Kodi uses 9090 by default")));
    hotKeyEdit->setToolTip(QString(tr("Set the global hotkey for showing and hiding Qore2")));

    resetButton = new QPushButton(tr("Defaults"));
    saveButton  = new QPushButton(tr("Save"));

    grid->setColumnMinimumWidth (2, 90);

    grid->addWidget(ipLabel,      0, 0, Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(portLabel,    1, 0, Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(hotKeyLabel,  0, 2, Qt::AlignRight | Qt::AlignVCenter);

    grid->addWidget(ipEdit,       0, 1);
    grid->addWidget(portEdit,     1, 1);
    grid->addWidget(hotKeyEdit,   0, 3, 1, 2);
    grid->addWidget(toggleButton, 3, 0, 1, 2, Qt::AlignBottom);

    grid->addWidget(resetButton,  3, 3, Qt::AlignBottom);
    grid->addWidget(saveButton,   3, 4, Qt::AlignBottom);

    setLayout(grid);

    connect(toggleButton, &QPushButton::pressed, this, &Settings::toggleMenuIconColor);
    connect(resetButton, &QPushButton::pressed, this, &Settings::resetSettings);
    connect(saveButton, &QPushButton::pressed, this, &Settings::saveSettings);
}


void Settings::toggleMenuIconColor()
{
    if (m_debug) {qDebug() << "Toggling dark theme icon color from" << darkTheme << "to" << !darkTheme;}

    // Since we want the icon to change when the button is pressed, it's better UX to save the state now incase the user
    // doesn't click save because they've already seen the toggle button taking effect
    darkTheme = !darkTheme;
    settings->setValue("darkTheme", darkTheme);

    m_trayIcon->setIcon(darkTheme ? QIcon(WHITE_ICON) : QIcon(BLACK_ICON));
}


void Settings::resetSettings()
{
    if (m_debug) {qDebug() << "Performing settings reset";}

    setDefaults(true);  // True we're doing a reset

    setupFromDisk();
}


void Settings::saveSettings()
{
    if (m_debug) {qDebug() << "Saving settings";}

    settings->setValue("ip", ipEdit->displayText());
    settings->setValue("port", portEdit->displayText());
    settings->setValue("hotkey", hotKeyEdit->keySequence().toString());

    setupFromDisk();
}
