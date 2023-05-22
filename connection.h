#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QtWebSockets/QWebSocket>

class Connection : public QWebSocket
{
    Q_OBJECT

public:
    Connection(bool debug = false);

public slots:
    void sendInputDotMethod(QString method);
    void sendExecuteActionMethod(QString action);
    void sendSendTextMethod(QString text);
    void setUrl(QString ip, QString port);

private slots:
    void onConnected();
    void onDisconnected();

private:
    void send(QJsonObject object);
    QUrl       m_url;
    QByteArray jsonAsByteArray;
    bool       m_debug;
};

#endif // CONNECTION_H
