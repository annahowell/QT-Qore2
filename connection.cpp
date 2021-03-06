#include "connection.h"

Connection::Connection(bool debug)
    : m_debug(debug)
{
    connect(&m_webSocket, &QWebSocket::connected,    this, &Connection::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Connection::onDisconnected);
}


void Connection::setUrl(QString url)
{
    // We're changing the url, so if the connection is open we should close it and let it attempt to reconnect next time
    // the remote is used
    if (m_webSocket.isValid()) {
        if (m_debug) {
            qDebug() << "Closing WebSocket";
        }

        m_webSocket.close();
    }

    if (m_debug) {
        qDebug() << "Setting WebSocket to: " << url;
    }

    m_url = QUrl(url);
}


void Connection::send(QJsonDocument jsonDoc)
{
    m_jsonDoc = jsonDoc;

    m_webSocket.open(m_url);
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
