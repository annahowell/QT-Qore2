#include "connection.h"

Connection::Connection()
{
    // Setup the webservice url
    serviceUrl.setUrl("http://kodi:kodi@192.168.1.200:8080/jsonrpc");

    // Call the webservice
    networkManager = new QNetworkAccessManager(this);

    // Send the network request
    networkRequest.setUrl(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
}


// -------------------------------------------------------------------------


void Connection::constructRequest(int buttonCode)
{
    QJsonObject action;
    QJsonObject json
    {
        {"jsonrpc", "2.0"},
        {"id", "1"}
    };

    switch (buttonCode) {

    case UP:
        json.insert("method", "Input.Up");
        break;

    case DOWN:
        json.insert("method", "Input.Down");
        break;

    case LEFT:
        json.insert("method", "Input.Left");
        break;

    case RIGHT:
        json.insert("method", "Input.Right");
        break;

    case ENTER:
        json.insert("method", "Input.Select");
        break;

    case BACK:
        json.insert("method", "Input.Back");
        break;

    case VOLUME_DOWN:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "volumedown");
        json.insert("params", action);
        break;

    case VOLUME_UP:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "volumeup");
        json.insert("params", action);
        break;

    case STOP:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "stop");
        json.insert("params", action);
        break;

    case PAUSE:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "pause");
        json.insert("params", action);
        break;

    case PLAY:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "play");
        json.insert("params", action);
        break;

    case PREVIOUS:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "skipprevious");
        json.insert("params", action);
        break;

    case REWIND:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "stepback");
        json.insert("params", action);
        break;

    case FAST_FORWARD:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "stepforward");
        json.insert("params", action);
        break;

    case NEXT:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "skipnext");
        json.insert("params", action);
        break;

    case SHOW_OSD:
        json.insert("method", "Input.ShowOSD");
        break;

    default:
        json.insert("method", "Input.noop");
        break;
    }

    reply = networkManager->post(networkRequest, QJsonDocument(json).toJson());

    while(!reply->isFinished())
    {
        qApp->processEvents();
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json_response = QJsonDocument::fromJson(response_data);
    qDebug() << "Received: " << json_response;
}


// -------------------------------------------------------------------------


void Connection::onPostAnswer(QNetworkReply* resp)
 {
    QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //status_code.is_valid(){
        // Print or catch the status code
        QString status = status_code.toString(); // or status_code.toInt();
        qDebug() << status;
    //}
 }
