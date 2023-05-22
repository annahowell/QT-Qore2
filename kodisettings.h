#ifndef KODISETTINGS_H
#define KODISETTINGS_H

#include <QtWidgets>
#include <QHotkey>
#include "connection.h"

class KodiSettings : public QWidget
{
    Q_OBJECT

public:
    KodiSettings(bool debug, QSettings *settings, QString instanceLetter, QString instanceNo);

    void populateWidgetsWithValuesFromDisk();
    void saveDefaultsToDisk();

public slots:
    void saveSettingsToDisk();
    void setDefaultIfSavedSettingsIsEmpty();

signals:
    void nicknameChangedSignal();

private slots:
    void saveSettingsToDiskAndEmitNicknameChangedSignal();

private:
    QString          m_instanceNo;
    bool             m_debug;
    QLineEdit        *nicknameEdit, *ipEdit, *portEdit, *userEdit, *passEdit;
    QString          m_instanceLetter;
    QSettings        *m_settings;

    void    createWidgets();
    QString getUrl();
};

#endif // KODISETTINGS_H
