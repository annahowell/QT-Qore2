#include "connection.h"

Connection::Connection(bool debug, QObject *parent) : QObject(parent), m_debug(debug)
{
    constructUrl();

    connect(&m_webSocket, &QWebSocket::connected,    this, &Connection::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Connection::onDisconnected);
}

void Connection::constructUrl()
{
    // We're changing the url, so if the connection is open we should close it
    // and let it attempt to reconnect next time the remote is used
    if (m_webSocket.isValid()) {
        m_webSocket.close();
    }

    url = nullptr;
    QString prefix = "ws://";
    QString ip = settings.value("ip").toString();
    QString seperator = ":";
    QString port = settings.value("port").toString();

    url.reserve(prefix.length() + ip.length() + seperator.length() + port.length());
    url.append(prefix);
    url.append(ip);
    url.append(seperator);
    url.append(port);

    if (m_debug) {
        qDebug() << "WebSocket server set to: " << url;
    }
}


void Connection::send(QJsonDocument jsonDoc)
{
    m_jsonDoc = jsonDoc;

    m_webSocket.open(QUrl(url));
}

void Connection::onConnected()
{
    if (m_debug) {
        qDebug() << "WebSocket connected";
    }

    connect(&m_webSocket, &QWebSocket::textFrameReceived, this, &Connection::onTextMessageReceived);

    m_webSocket.sendTextMessage(m_jsonDoc.toJson());
}

void Connection::onTextMessageReceived(QString message)
{
    if (m_debug) {
        qDebug() << "Message received:" << message;
    }

}

void Connection::onDisconnected()
{
    if (m_debug) {
        qDebug() << "WebSocket disconnected";
    }

}

Connection::~Connection()
{
    if (m_debug) {
        qDebug() << "Application quitting - closing connection";
    }

    m_webSocket.close();
}
