#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QtWebSockets/QWebSocket>

#define UP           0
#define DOWN         1
#define LEFT         2
#define RIGHT        3
#define ENTER        4
#define BACK         5
#define VOLUME_UP    6
#define VOLUME_DOWN  7
#define STOP         8
#define PAUSE        9
#define PLAY         10
#define PREVIOUS     11
#define REWIND       12
#define FAST_FORWARD 13
#define NEXT         14
#define SHOW_OSD     15


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
