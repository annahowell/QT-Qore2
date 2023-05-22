#include <QCloseEvent>
#include <QSystemTrayIcon>
#include "settings.h"
#include "kodisettings.h"

Settings::Settings(bool debug, QHotkey *hotkey)
    :  m_debug(debug), m_hotkey(hotkey)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:Settings()";
    }

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

    settings = new QSettings("AnnaHowell", "002", this);

    // If settings doesn't contain 'hotkey' we can be pretty sure this is a fresh install, so write defaults to disk
    if (!settings->contains("hotkey")) {
        qDebug() << "Qore2: Settings:Settings() determined 'hotkey' not in config, assuming fresh install and setting defaults";

        saveDefaultsToDisk(false); // False not requested by the user
    }

    // We can safely create our widgets now, because TrayApp is yet to call trayIcon->show()
    createWidgets();

    populateWidgetsWithValuesFromDisk();
}


void Settings::createWidgets()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:createWidgets()";
    }

    // Create the grid
    QGridLayout *grid = new QGridLayout(this);

    // Create hotkey elements
    const QString *hotkeyMsg = new const QString(tr("Set the global hotkey for showing and hiding the remote"));
    QLabel *hotKeyLabel = new QLabel(tr("Hotkey:"), this);
    hotKeyLabel->setToolTip(*hotkeyMsg);
    hotKeyEdit = new QKeySequenceEdit(this);
    hotKeyEdit->setToolTip(*hotkeyMsg);

    // Create our kodi connection settings tab widget
    tabWidget = new QTabWidget(this);

    // Loop over the maximum number of Kodis'
    for (int i = 0; i < KODI_COUNT; i++) {
        QString stringI = QString::number(i);

        // Determine the instance letter for this loop, so for loop 0 the letter is A, for loop 1 the letter is B, etc
        QString instanceLetter = QString::fromUtf8("ABC").mid(i, 1);

        // Actually instantiate KodiSettings passing userRequested to it
        kodiSettings[i] = new KodiSettings(m_debug, settings, instanceLetter, stringI);

        // Otherwise add the KodiSettings instance to a Tab with a default nickname
        if (!settings->contains("nickname" + stringI)) {
            tabWidget->addTab(kodiSettings[i], QString::fromUtf8("Kodi") + instanceLetter);

        // Or a custom nickname
        } else {
            tabWidget->addTab(kodiSettings[i], settings->value("nickname" + stringI).toString());
        }

        // Set the tooltip
        tabWidget->setTabToolTip(i, QString::fromUtf8("Set the connection details for Kodi instance nicknamed ") + settings->value("nickname" + instanceLetter).toString());

        // And finally connect the nickname changed signal
        connect(kodiSettings[i], &KodiSettings::nicknameChangedSignal, this, &Settings::updateCurrentTabLabel);
    }

    // Create defaults button
    QPushButton *defaultButton  = new QPushButton(tr("Defaults"), this);
    defaultButton->setToolTip("Reset all settings to default");


    // |------------------------------------------------------------------|
    // |   Hotkey Label |  Hotkey Edit  |              |                  |
    // |------------------------------------------------------------------|
    // |                                                                  |
    // |              [ Kodi TabA | Kodi TabB | Kodi TabC ]               |
    // |    Nick Label   |	Nick Edit	|              |                  |
    // |   ------------------------------------------------------------   |
    // |    IP Label     |	IP Edit		|  Port Label  |   Port Edit      |
    // |                                                                  |
    // |------------------------------------------------------------------|
    // |  [Default Btn]  |	            |              |                  |
    // |------------------------------------------------------------------|
    //
    // Add hotkey elements top left
    //
    //              widget       Row, Col, (Alignment)
    //              widget       Row, Col, (RowSpan, ColSpan, Alignment)
    grid->addWidget(hotKeyLabel, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(hotKeyEdit,  0, 1, 1, 1);

    // Enforce column stretch. This started as all 5 columns adding up to 100, but this didn't provide enough
    // granularity, so all values should add up to 400 now. Thus the value 82 below can be thought of as 20.5%, and the
    // value 36 can be thought of as 9%
    grid->setColumnStretch(0, 87);
    grid->setColumnStretch(1, 120);
    grid->setColumnStretch(2, 69);
    grid->setColumnStretch(3, 88);
    grid->setColumnStretch(4, 36);

    // Add some hacky row spacing above tabs on the second row
    grid->setRowMinimumHeight(1, 30);

    // Add tab widget in the middle
    grid->addWidget(tabWidget, 2, 0, 1, 5, Qt::AlignBottom);

    // Add some more hacky spacing on the row below the tabs AKA the fourth row
    grid->setRowMinimumHeight(3, 10);

    // Add the reset button to the bottom left
    grid->addWidget(defaultButton, 4, 0, 1, 5, Qt::AlignLeft |  Qt::AlignBottom);

    setLayout(grid);

    connect(hotKeyEdit, &QKeySequenceEdit::keySequenceChanged, this, &Settings::saveSettingsToDisk);
    connect(tabWidget, &QTabWidget::currentChanged, this, &Settings::emitTabIndexChangedSignal);
    connect(defaultButton, &QPushButton::pressed, this, &Settings::showSetDefaultsConfirmation);
}


void Settings::showSetDefaultsConfirmation()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:showSetDefaultsConfirmation()";
    }

    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to reset all settings?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int response = msgBox.exec();

    switch (response) {
        case QMessageBox::Ok:
            qDebug() << "Qore2: showSetDefaultsConfirmation() received Ok response";

             saveDefaultsToDisk(true); // True this was requested by the user
             populateWidgetsWithValuesFromDisk();
            break;

        default:
            qDebug() << "Qore2: showSetDefaultsConfirmation() received Cancel response";
            break;
    }
}


void Settings::saveDefaultsToDisk(bool requestedByUser = false)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:saveDefaultsToDisk(requestedByUser) with requestedByUser"<<requestedByUser;
    }

    settings->setValue("darkTheme", false);
    settings->setValue("hotkey", QKeySequence(Qt::ControlModifier | Qt::Key_1).toString());

    if (!requestedByUser) {
        return;
    }

    for (int i = 0; i < KODI_COUNT; i++) {
        kodiSettings[i]->saveDefaultsToDisk();
        kodiSettings[i]->populateWidgetsWithValuesFromDisk();
    }

    emit setUseLightThemeSignal(true);
}


void Settings::populateWidgetsWithValuesFromDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:populateWidgetsWithValuesFromDisk()";
    }

    // Set the tray icon
    darkTheme = settings->value("darkTheme").toBool();

    // Set the hotkey
    m_hotkey->setRegistered(false);

    hotKeyEdit->setKeySequence(QKeySequence::fromString(settings->value("hotkey").toString()));
    m_hotkey->setShortcut(QKeySequence::fromString(settings->value("hotkey").toString()));
    m_hotkey->setRegistered(true);

    for (int i = 0; i < KODI_COUNT; i++) {
        tabWidget->setTabText(i, QString::fromUtf8("Kodi") + QString::fromUtf8("ABC").mid(i, 1));
    }
}


void Settings::toggleIconTheme()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:toggleIconTheme()";
    }

    if (m_debug) {
        qDebug() << "Qore2: Toggling dark theme icon color from" << darkTheme << "to" << !darkTheme;
    }

    darkTheme = !darkTheme;
    settings->setValue("darkTheme", darkTheme);
}


void Settings::saveSettingsToDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:saveSettingsToDisk()";
    }

    settings->setValue("hotkey", hotKeyEdit->keySequence().toString());

    populateWidgetsWithValuesFromDisk();
}


void Settings::emitTabIndexChangedSignal()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:emitTabIndexChangedSignal()";
    }

    emit tabIndexChangedSignal(tabWidget->currentIndex());
}


void Settings::saveTabIndexToDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:saveTabIndexToDisk() and saving tabIndex as"<<tabWidget->currentIndex();
    }

    settings->setValue("tabIndex", tabWidget->currentIndex());
}


bool Settings::getDarkTheme()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:getDarkTheme()";
    }

    return darkTheme;
}


QString Settings::getNicknameByIndex(int index)
{
    return settings->value("nickname" + QString::number(index)).toString();
}


QString Settings::getCurrentIP()
{
    return settings->value("ip" + QString::number(tabWidget->currentIndex())).toString();
}


QString Settings::getCurrentPort()
{
    return settings->value("port" + QString::number(tabWidget->currentIndex())).toString();
}


void Settings::updateCurrentTabLabel()
{
    updateTabLabelByIndex(tabWidget->currentIndex());
}


void Settings::updateTabLabelByIndex(int tabIndex)
{
    QString tabText = settings->value("nickname" + QString::number(tabIndex)).toString();

    if (tabText.isEmpty()) {
        tabText = QString::fromUtf8("Kodi") + QString::fromUtf8("ABC").mid(tabIndex, 1);
    }


    tabWidget->setTabText(tabIndex, tabText);
}


void Settings::updateTabIndexFromDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:updateTabIndexFromDisk() and found currently saved tabIndex was"<<settings->value("tabIndex").toString();
    }

    tabWidget->setCurrentIndex(settings->value("tabIndex").toInt());
}


void Settings::closeEvent(QCloseEvent *event)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Settings:closeEvent()";
    }

    event->ignore();

    saveSettingsToDisk();

    // Loop over the maximum number of Kodis'
    for (int i = 0; i < KODI_COUNT; i++) {
        kodiSettings[i]->saveSettingsToDisk();
        kodiSettings[i]->setDefaultIfSavedSettingsIsEmpty();
        kodiSettings[i]->populateWidgetsWithValuesFromDisk();
    }

    emit settingsCloseEventSignal(getCurrentIP(), getCurrentPort());

    accept();
}
