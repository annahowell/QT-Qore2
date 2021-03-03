#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QtWebSockets/QWebSocket>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(bool debug = false, QObject *parent = nullptr);
    void constructUrl();
    void send(QJsonDocument jsonDoc);
    ~Connection();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);

private:
    QSettings settings;
    QWebSocket m_webSocket;
    QString url;
    QJsonDocument m_jsonDoc;
    bool m_debug;
};

#endif // CONNECTION_H
