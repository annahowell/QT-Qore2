#include "connection.h"

Connection::Connection(bool debug)
    : m_debug(debug)
{
    connect(this, &QWebSocket::connected, this, &Connection::onConnected);
    connect(this, &QWebSocket::disconnected, this, &Connection::onDisconnected);
}


void Connection::setUrl(QString url)
{
    // We're changing the url, so if the connection is open we should close it and let it attempt to reconnect next time
    // the remote is used
    if (isValid()) {
        if (m_debug) {qDebug() << "Closing WebSocket";}

        close();
    }

    if (m_debug) {qDebug() << "Setting WebSocket to:" << url;}

    m_url = QUrl(url);
}


void Connection::send(QJsonDocument jsonDoc)
{
    if (m_debug) {qDebug() << "Sending:" << jsonDoc;}

    jsonAsByteArray = jsonDoc.toJson();

    if (isValid()) {
        sendTextMessage(jsonAsByteArray);
    } else {
        open(m_url);
    }
}


void Connection::onConnected()
{
    if (m_debug) {qDebug() << "WebSocket connected";}

    sendTextMessage(jsonAsByteArray);
}


void Connection::onDisconnected()
{
    if (m_debug) {qDebug() << "WebSocket disconnected";}
}
