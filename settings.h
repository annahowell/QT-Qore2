#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets>
#include <QHotkey>
#include "kodisettings.h"

#define BLACK_ICON         ":/icons/tray-icon-black.svg"
#define WHITE_ICON         ":/icons/tray-icon-white.svg"

class Settings : public QDialog
{
    Q_OBJECT

public:
    Settings(bool debug, QHotkey *hotkey);
    void toggleIconTheme();
    bool getDarkTheme();
    void updateTabIndexFromDisk();
    void updateTabLabelByIndex(int tabIndex);
    QString getCurrentIP();
    QString getCurrentPort();
    QString getNicknameByIndex(int index);

public slots:
    void saveTabIndexToDisk();
    void updateCurrentTabLabel();

signals:
    void tabIndexChangedSignal(int currentIndex);
    void settingsCloseEventSignal(QString ip, QString port);
    void setUseLightThemeSignal(bool useLightTheme);

private slots:
    void showSetDefaultsConfirmation();
    void saveSettingsToDisk();
    void emitTabIndexChangedSignal();

private:
    const int KODI_COUNT = 3;

    bool             darkTheme, m_debug;
    QKeySequenceEdit *hotKeyEdit;
    QLineEdit        *nicknameEdit;
    QSettings        *settings;
    QHotkey          *m_hotkey;
    KodiSettings     *kodiSettings[3];
    QTabWidget       *tabWidget;

    void saveDefaultsToDisk(bool requestedByUser);
    void populateWidgetsWithValuesFromDisk();
    void createWidgets();

protected:
    void closeEvent (QCloseEvent *event);
};

#endif // SETTINGS_H
