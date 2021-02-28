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

    if (!s.contains("up")          || doReset) {s.setValue("up",          "up");}
    if (!s.contains("down")        || doReset) {s.setValue("down",        "down");}
    if (!s.contains("left")        || doReset) {s.setValue("left",        "left");}
    if (!s.contains("right")       || doReset) {s.setValue("right",       "right");}
    if (!s.contains("enter")       || doReset) {s.setValue("enter",       "return");}
    if (!s.contains("back")        || doReset) {s.setValue("back",        "backspace");}

    if (!s.contains("volumeup")    || doReset) {s.setValue("volumeup",    "=");}
    if (!s.contains("volumedown")  || doReset) {s.setValue("volumedown",  "-");}

    if (!s.contains("stop")        || doReset) {s.setValue("stop",        "x");}
    if (!s.contains("pause")       || doReset) {s.setValue("pause",       "space");}
    if (!s.contains("previous")    || doReset) {s.setValue("previous",    "[");}
    if (!s.contains("rewind")      || doReset) {s.setValue("rewind",      "ctrl+left");}
    if (!s.contains("fastforward") || doReset) {s.setValue("fastforward", "ctrl+right");}
    if (!s.contains("next")        || doReset) {s.setValue("next",        "]");}
    if (!s.contains("showosd")     || doReset) {s.setValue("showosd",     "m");}
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
    usernameLabel = new QLabel(tr("User "));
    usernameEdit = new QLineEdit(s.value("username").toString());
    passwordLabel = new QLabel(tr("Pass "));
    passwordEdit = new QLineEdit(s.value("password").toString());

    upLabel = new QLabel(tr("Up "));
    upEdit = new QLineEdit(s.value("up").toString());
    downLabel = new QLabel(tr("Down "));
    downEdit = new QLineEdit(s.value("down").toString());
    leftLabel = new QLabel(tr("Left "));
    leftEdit = new QLineEdit(s.value("left").toString());
    rightLabel = new QLabel(tr("Right "));
    rightEdit = new QLineEdit(s.value("right").toString());
    enterLabel = new QLabel(tr("Select "));
    enterEdit = new QLineEdit(s.value("enter").toString());
    backLabel = new QLabel(tr("Back "));
    backEdit = new QLineEdit(s.value("back").toString());

    volumeDownLabel = new QLabel(tr("Volume- "));
    volumeDownEdit = new QLineEdit(s.value("volumedown").toString());
    volumeUpLabel = new QLabel(tr("Volume+ "));
    volumeUpEdit = new QLineEdit(s.value("volumeup").toString());

    stopLabel = new QLabel(tr("Stop "));
    stopEdit = new QLineEdit(s.value("stop").toString());
    pauseLabel = new QLabel(tr("Pause "));
    pauseEdit = new QLineEdit(s.value("pause").toString());
    previousLabel = new QLabel(tr("Previous "));
    previousEdit = new QLineEdit(s.value("previous").toString());
    rewindLabel = new QLabel(tr("Rewind "));
    rewindEdit = new QLineEdit(s.value("rewind").toString());
    fastForwardLabel = new QLabel(tr("F.Forward "));
    fastForwardEdit = new QLineEdit(s.value("fastforward").toString());
    nextLabel = new QLabel(tr("Next "));
    nextEdit = new QLineEdit(s.value("next").toString());
    showOsdLabel = new QLabel(tr("OSD "));
    showOsdEdit = new QLineEdit(s.value("showosd").toString());

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
    usernameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    passwordLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    upLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    downLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    rightLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    enterLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    backLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    volumeDownLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    volumeUpLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    stopLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    pauseLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    previousLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    rewindLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    fastForwardLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    nextLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    showOsdLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    portLabel->setContentsMargins(0, 0, 0, 15);
    portEdit->setContentsMargins(0, 0, 0, 15);
    passwordLabel->setContentsMargins(0, 0, 0, 15);
    passwordEdit->setContentsMargins(0, 0, 0, 15);

    enterLabel->setContentsMargins(0, 0, 0, 15);
    enterEdit->setContentsMargins(0, 0, 0, 15);
    backLabel->setContentsMargins(0, 0, 0, 15);
    backEdit->setContentsMargins(0, 0, 0, 15);
}


// -------------------------------------------------------------------------


void Settings::setUpLayout()
{
    grid->addWidget(ipLabel, 0, 0);
    grid->addWidget(ipEdit, 0, 1);
    grid->addWidget(portLabel, 1, 0);
    grid->addWidget(portEdit, 1, 1);
    grid->addWidget(usernameLabel, 0, 2);
    grid->addWidget(usernameEdit, 0, 3);
    grid->addWidget(passwordLabel, 1, 2);
    grid->addWidget(passwordEdit, 1, 3);

    grid->addWidget(upLabel, 2, 0);
    grid->addWidget(upEdit, 2, 1);
    grid->addWidget(downLabel, 3, 0);
    grid->addWidget(downEdit, 3, 1);
    grid->addWidget(leftLabel, 2, 2);
    grid->addWidget(leftEdit, 2, 3);
    grid->addWidget(rightLabel, 3, 2);
    grid->addWidget(rightEdit, 3, 3);
    grid->addWidget(enterLabel, 4, 0);
    grid->addWidget(enterEdit, 4, 1);
    grid->addWidget(backLabel, 4, 2);
    grid->addWidget(backEdit, 4, 3);

    grid->addWidget(volumeDownLabel, 5, 0);
    grid->addWidget(volumeDownEdit, 5, 1);
    grid->addWidget(volumeUpLabel, 5, 2);
    grid->addWidget(volumeUpEdit, 5, 3);

    grid->addWidget(stopLabel, 6, 0);
    grid->addWidget(stopEdit, 6, 1);
    grid->addWidget(pauseLabel, 6, 2);
    grid->addWidget(pauseEdit, 6, 3);
    grid->addWidget(previousLabel, 7, 0);
    grid->addWidget(previousEdit, 7, 1);
    grid->addWidget(nextLabel, 7, 2);
    grid->addWidget(nextEdit, 7, 3);
    grid->addWidget(rewindLabel, 8, 0);
    grid->addWidget(rewindEdit, 8, 1);
    grid->addWidget(fastForwardLabel, 8, 2);
    grid->addWidget(fastForwardEdit, 8, 3);
    grid->addWidget(showOsdLabel, 9, 0);
    grid->addWidget(showOsdEdit, 9, 1);

    grid->addWidget(resetButton, 10, 2);
    grid->addWidget(saveButton, 10, 3);
}


// -------------------------------------------------------------------------


void Settings::saveSettings()
{
    qDebug() << ipEdit->displayText();
    s.setValue("ip", ipEdit->displayText());
    s.setValue("port", portEdit->displayText());
    s.setValue("username", usernameEdit->displayText());
    s.setValue("password", passwordEdit->displayText());

    s.setValue("up", upEdit->displayText());
    s.setValue("down", downEdit->displayText());
    s.setValue("left", leftEdit->displayText());
    s.setValue("right", rightEdit->displayText());
    s.setValue("enter", enterEdit->displayText());
    s.setValue("back", backEdit->displayText());

    s.setValue("volumedown", volumeDownEdit->displayText());
    s.setValue("volumeup", volumeUpEdit->displayText());

    s.setValue("stop", stopEdit->displayText());
    s.setValue("pause", pauseEdit->displayText());
    s.setValue("previous", previousEdit->displayText());
    s.setValue("rewind", rewindEdit->displayText());
    s.setValue("fastforward", fastForwardEdit->displayText());
    s.setValue("next", nextEdit->displayText());
    s.setValue("showosd",showOsdEdit->displayText());
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
    usernameEdit->setText(s.value("username").toString());
    passwordEdit->setText(s.value("password").toString());

    upEdit->setText(s.value("up").toString());
    downEdit->setText(s.value("down").toString());
    leftEdit->setText(s.value("left").toString());
    rightEdit->setText(s.value("right").toString());
    enterEdit->setText(s.value("enter").toString());
    backEdit->setText(s.value("back").toString());

    volumeDownEdit->setText(s.value("volumedown").toString());
    volumeUpEdit->setText(s.value("volumeup").toString());

    stopEdit->setText(s.value("stop").toString());
    pauseEdit->setText(s.value("pause").toString());
    previousEdit->setText(s.value("previous").toString());
    rewindEdit->setText(s.value("rewind").toString());
    fastForwardEdit->setText(s.value("fastforward").toString());
    nextEdit->setText(s.value("next").toString());
    showOsdEdit->setText(s.value("showosd").toString());
}
