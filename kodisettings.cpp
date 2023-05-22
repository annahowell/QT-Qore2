#include <QCloseEvent>
#include "kodisettings.h"

KodiSettings::KodiSettings(bool debug, QSettings *settings, QString instanceLetter, QString instanceNo)
    : m_debug(debug),
      m_settings(settings),
      m_instanceLetter(instanceLetter),
      m_instanceNo(instanceNo)
{

    if (m_debug) {
        qDebug() << "Qore2: Running KodiSettings::KodiSettings with instanceLetter"<<instanceLetter<<"instanceNo"<<instanceNo;
    }

    createWidgets();

    // If settings doesn't contain 'ipX' we can be pretty sure this is a fresh install, so write defaults to disk
    if (!m_settings->contains("ip" + m_instanceNo)) {
        qDebug() << "Qore2: KodiSettings:KodiSettings() (IN:"<<m_instanceNo<<") determined"<<"ip"+m_instanceNo<<"not in config, assuming fresh install and setting defaults";

        saveDefaultsToDisk();
    }

    populateWidgetsWithValuesFromDisk();
}


void KodiSettings::saveDefaultsToDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running KodiSettings:saveDefaultsToDisk() (IL:"<<m_instanceNo<<")";
    }

    m_settings->setValue("nickname" + m_instanceNo, "Kodi" + m_instanceLetter);
    m_settings->setValue("ip" + m_instanceNo, (QString::fromUtf8("192.168.10.10") + m_instanceNo));
    m_settings->setValue("port" + m_instanceNo,  9090);
}


void KodiSettings::populateWidgetsWithValuesFromDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running KodiSettings::populateWidgetsWithValuesFromDisk() (IN:"<<m_instanceNo<<")";
    }

    nicknameEdit->setText(m_settings->value("nickname" + m_instanceNo).toString());
    ipEdit->setText(m_settings->value("ip" + m_instanceNo).toString());
    portEdit->setText(m_settings->value("port" + m_instanceNo).toString());
}


void KodiSettings::createWidgets()
{
    if (m_debug) {
        qDebug() << "Qore2: Running KodiSettings::createWidgets() (IN:"<<m_instanceNo<<")";
    }

    // Create the grid
    QGridLayout *grid = new QGridLayout(this);

    // Create nickname elements
    const QString *nicknameMsg = new const QString(tr("Set a nickname for this instance of Kodi"));

    QLabel *nicknameLabel = new QLabel(tr("Nickname:"), this);
    nicknameLabel->setToolTip(*nicknameMsg);
    nicknameEdit = new QLineEdit(this);
    nicknameEdit->setToolTip(*nicknameMsg);
    nicknameEdit->setMaxLength(10);
    nicknameEdit->setPlaceholderText("Kodi" + m_instanceLetter);

    // Create IP elements
    const QString *ipMsg = new const QString(tr("Set the IP address or hostname for this instance of Kodi"));
    QLabel *ipLabel = new QLabel(tr("IP / Host:"), this);
    ipLabel->setToolTip(*ipMsg);
    ipEdit = new QLineEdit(this);
    ipEdit->setToolTip(*ipMsg);
    ipEdit->setPlaceholderText("192.168.10.10" + m_instanceNo);


    // Create port elements
    const QString *portMsg = new const QString(tr("Set the websocket port for this instance of Kodi.The default is 9090."));
    QLabel *portLabel = new QLabel(tr("Port:"), this);
    portLabel->setToolTip(*portMsg);
    portEdit = new QLineEdit(this);
    portEdit->setValidator(new QIntValidator(this));
    portEdit->setToolTip(*portMsg);
    portEdit->setPlaceholderText("9090");

    // Connect QLineEdits to saveSettingsToDisk()
    connect(nicknameEdit, &QLineEdit::textEdited, this, &KodiSettings::saveSettingsToDiskAndEmitNicknameChangedSignal);
    connect(ipEdit, &QLineEdit::textEdited, this, &KodiSettings::saveSettingsToDisk);
    connect(portEdit, &QLineEdit::textEdited, this, &KodiSettings::saveSettingsToDisk);

    // |------------------------------------------------------------------|
    // | Nickname Label |  NicknameEdit |               |                 |
    // |------------------------------------------------------------------|
    // |   IP Label     |  IP Edit      |   Port Label  |   Port Edit     |
    // |------------------------------------------------------------------|
    //
    // Add nickname elements top left
    //
    //              widget       Row, Col, (Alignment)
    //              widget       Row, Col, (RowSpan, ColSpan, Alignment)
    grid->addWidget(nicknameLabel, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(nicknameEdit,  0, 1);

    // Add IP elements bottom left
    grid->addWidget(ipLabel,   1, 0, Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(ipEdit,   1, 1);

    // Enforce minimum space in third column
    grid->setColumnStretch(0, 17);
    grid->setColumnStretch(1, 33);
    grid->setColumnStretch(2, 20);
    grid->setColumnStretch(3, 30);

    // Add Port elements bottom right
    grid->addWidget(portLabel, 1, 2, Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(portEdit, 1, 3);

    setLayout(grid);
}


void KodiSettings::saveSettingsToDisk()
{
    if (m_debug) {
        qDebug() << "Qore2: Running KodiSettings::saveSettingsToDisk() (IN:"<<m_instanceNo<<")";
    }

    m_settings->setValue("nickname" + m_instanceNo, nicknameEdit->displayText());
    m_settings->setValue("ip" + m_instanceNo, ipEdit->displayText());
    m_settings->setValue("port" + m_instanceNo, portEdit->displayText());

    populateWidgetsWithValuesFromDisk();
}


void KodiSettings::setDefaultIfSavedSettingsIsEmpty()
{
    if (m_debug) {
        qDebug() << "Qore2: Running KodiSettings::validateSavedSettings() (IN:"<<m_instanceNo<<")";
    }

    QString nickname = m_settings->value("nickname" + m_instanceNo).toString();
    QString ip       = m_settings->value("ip" + m_instanceNo).toString();
    QString port     = m_settings->value("port" + m_instanceNo).toString();

    if (nickname.isEmpty()) {
        m_settings->setValue("nickname" + m_instanceNo, "Kodi" + m_instanceLetter);

        emit nicknameChangedSignal();
    }

    if (ip.isEmpty()) {
        m_settings->setValue("ip" + m_instanceNo, (QString::fromUtf8("192.168.10.10") + m_instanceNo));
    }

    if (port.isEmpty()) {
        m_settings->setValue("port" + m_instanceNo,  9090);
    }

    populateWidgetsWithValuesFromDisk();
}



void KodiSettings::saveSettingsToDiskAndEmitNicknameChangedSignal()
{
    if (m_debug) {
        qDebug() << "Qore2: Running KodiSettings::saveSettingsToDiskAndEmitNicknameChangedSignal() (IN:"<<m_instanceNo<<")";
    }

    saveSettingsToDisk();

    emit nicknameChangedSignal();
}

