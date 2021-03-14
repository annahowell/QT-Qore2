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

public slots:
    void sendInputDotMethod(QString method);
    void sendExecuteActionMethod(QString action);
    void sendSendTextMethod(QString text);

private slots:
    void onConnected();
    void onDisconnected();

private:
    void send(QJsonObject object);

    bool       m_debug;
    QUrl       m_url;
    QByteArray jsonAsByteArray;
};

#endif // CONNECTION_H
