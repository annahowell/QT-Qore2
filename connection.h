#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QtWebSockets/QWebSocket>

class Connection : public QObject
{
    Q_OBJECT

public:
    explicit Connection(bool debug = false);
    void setUrl(QString url);
    void send(QJsonDocument jsonDoc);
    ~Connection();

Q_SIGNALS:
    void closed();

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket    m_webSocket;
    QUrl          m_url;
    QJsonDocument m_jsonDoc;
    bool m_debug;
};

#endif // CONNECTION_H
