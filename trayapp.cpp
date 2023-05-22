#include "trayapp.h"

TrayApp::TrayApp()
{
}


void TrayApp::toggleIconTheme()
{
    if (debug) {
        qDebug() << "Qore2: Running TrayApp::toggleIconTheme()";
    }

    settings->toggleIconTheme();

    trayIcon->setIcon(settings->getDarkTheme() ? QIcon(BLACK_ICON) : QIcon(WHITE_ICON));
}


void TrayApp::handleTabIndexChangedSlot(int currentTabIndex)
{
    if (debug) {
        qDebug() << "Qore2: Running TrayApp::handleTabIndexChangedSlot() with currentIndex"<<currentTabIndex;
    }

    this->currentTabIndex = currentTabIndex;

    settings->saveTabIndexToDisk();

    connection->setUrl(settings->getCurrentIP(), settings->getCurrentPort());

    toggleIconTheme();
}


void TrayApp::handlenicknameChangedSlot()
{
    if (debug) {
        qDebug() << "Qore2: Running TrayApp::handlenicknameChangedSlot() and currentTabIndex is"<<currentTabIndex;
    }

    settings->updateTabLabelByIndex(currentTabIndex);
}


void TrayApp::showPreferences()
{
    if (debug) {
        qDebug() << "Qore2: Running TrayApp::showPreferences()";
    }

    settingsOpened = true;

    if (remoteOpened) {
        toggleVisibility();
    }

    settings->updateTabIndexFromDisk();
    settings->show();
    settings->setFocus();
    settings->activateWindow();
    settings->raise();
}



