#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QtWebSockets/QWebSocket>

class Connection : public QWebSocket
{
    Q_OBJECT

public:
    Connection(bool debug = false);
    void setUrl(QString url);
    void send(QJsonDocument jsonDoc);

private slots:
    void onConnected();
    void onDisconnected();

private:
    bool       m_debug;
    QUrl       m_url;
    QByteArray jsonAsByteArray;
};

#endif // CONNECTION_H
