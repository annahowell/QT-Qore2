#include "connection.h"

Connection::Connection(bool debug)
    : m_debug(debug)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::Connection()";
    }

    connect(this, &QWebSocket::connected, this, &Connection::onConnected);
    connect(this, &QWebSocket::disconnected, this, &Connection::onDisconnected);
}


void Connection::setUrl(QString ip, QString port)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::setUrl(ip, port) with ip"<<ip<<" and port"<<port;
    }

    // We're changing the url, so if the connection is open we should close it and let it attempt to reconnect next time
    // the remote is used
    if (isValid()) {
        if (m_debug) {
            qDebug() << "Qore2: Closing WebSocket";
        }

        close();
    }

    // Set the connection url
    QString url = nullptr;
    QString prefix = "ws://";
    QString seperator = ":";

    url.reserve(prefix.length() + ip.length() + seperator.length() + port.length());
    url.append(prefix).append(ip).append(seperator).append(port);

    if (m_debug) {
        qDebug() << "Qore2: Setting WebSocket to:" << url;
    }

    m_url = QUrl(url);
}


void Connection::sendInputDotMethod(QString method)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::sendInputDotMethod(method) with method " << method;
    }

    send(QJsonObject {
        {"jsonrpc", "2.0"},
        {"id",      "1"},
        {"method",  "Input." + method}
    });
}


void Connection::sendExecuteActionMethod(QString action)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::sendExecuteActionMethod(action) with action " << action;
    }

    send(QJsonObject {
       {"jsonrpc", "2.0"},
       {"id", "1"},
       {"method",  "Input.ExecuteAction"},
       {"params", QJsonObject {
               {"action", action}
           }
       }
    });
}


void Connection::sendSendTextMethod(QString text)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::sendSendTextMethod(text) with text " << text;
    }

    send(QJsonObject {
       {"jsonrpc", "2.0"},
       {"id", "1"},
       {"method", "Input.SendText"},
       {"params", QJsonObject {
               {"text", text}
           }
       }
    });
}


void Connection::send(QJsonObject object)
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::send()";
    }

    if (m_debug) {
        qDebug() << "Qore: Sending:" << object;
    }

    jsonAsByteArray = QJsonDocument(object).toJson();

    if (isValid()) {
        sendTextMessage(jsonAsByteArray);
    } else {
        open(m_url);
    }
}


void Connection::onConnected()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::onConnected() (WebSocket is connected)";
    }

    sendTextMessage(jsonAsByteArray);
}


void Connection::onDisconnected()
{
    if (m_debug) {
        qDebug() << "Qore2: Running Connection::onDisconnected() (WebSocket is disconnected)";
    }
}
