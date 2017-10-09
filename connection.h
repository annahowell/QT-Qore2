#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>

// Button codes, used to make program more readable, all
// usages converted to int equivalents at compile time
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
    Connection();
    void constructRequest(int buttonCode);

public slots:
    void onPostAnswer(QNetworkReply* reponse);

private:
    QUrl serviceUrl;
    QNetworkAccessManager *networkManager;
    QNetworkRequest networkRequest;
    QNetworkReply *reply;
    QSettings *s;
};

#endif // CONNECTION_H
