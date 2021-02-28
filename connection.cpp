#include "connection.h"

Connection::Connection(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (true)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &Connection::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Connection::closed);
}

void Connection::send(QJsonDocument jsondoc)
{
    jsonDocument = jsondoc;

    m_webSocket.open(QUrl(m_url));
}

void Connection::onConnected()
{
    if (m_debug) {
        qDebug() << "WebSocket connected";
    }

    connect(&m_webSocket, &QWebSocket::textFrameReceived, this, &Connection::onTextMessageReceived);


    m_webSocket.sendTextMessage(jsonDocument.toJson());
}

void Connection::onTextMessageReceived(QString message)
{
    if (m_debug) {
        qDebug() << "Message received:" << message;
    }

}

Connection::~Connection()
{
    if (m_debug) {
        qDebug() << "Closing connection";
    }

    m_webSocket.close();
}
