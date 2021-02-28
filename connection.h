#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QtWebSockets/QWebSocket>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(const QUrl &url, bool debug = false, QObject *parent = nullptr);
    void send(QJsonDocument jsondoc);
    ~Connection();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    QJsonDocument jsonDocument;
    bool m_debug;
};

#endif // CONNECTION_H
