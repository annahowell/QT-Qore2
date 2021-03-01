#include "remotecontrol.h"

RemoteControl::RemoteControl()
{
    connection = new Connection(QUrl(QStringLiteral("ws://192.168.9.201:9090")), true);

    createWidgets();
    setShortcuts();
    setUpLayout();
}


// -------------------------------------------------------------------------


void RemoteControl::createWidgets()
{
    // Create buttons
    up          = new QPushButton("↑");
    down        = new QPushButton("↓");
    left        = new QPushButton("←");
    right       = new QPushButton("→");
    enter       = new QPushButton(" ");

    volumeUp    = new QPushButton("+");
    volumeLogo  = new QPushButton(style()->standardIcon(QStyle::SP_MediaVolume), "");
    volumeDown  = new QPushButton("-");

    home        = new QPushButton("Home");
    previous    = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipBackward), "");
    stop        = new QPushButton(style()->standardIcon(QStyle::SP_MediaStop), "");
    playPause   = new QPushButton(style()->standardIcon(QStyle::SP_MediaPlay), "");
    next        = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipForward), "");

    info        = new QPushButton("Info");
    menu        = new QPushButton("Menu");
    back        = new QPushButton("Back");


    //sendText    = new QLineEdit("");

    // Create array so we can foreach through adding default values for every button
    buttons << up       << down       << left       << right << enter \
            << volumeUp << volumeLogo << volumeDown                   \
            << previous << stop       << playPause  << next           \
            << home     << info       << menu       << back;

    signalMapper = new QSignalMapper(this);

    for(auto& button : buttons)
    {
      //button->setStyleSheet("background-color: red");
      button->setFixedSize(QSize(42, 40));
      button->setFlat(false);
      button->setIconSize(QSize(20,20));
      connect (button, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
    }

    // Now set the non-square buttons
    home->setFixedSize(QSize(80, 40));
    info->setFixedSize(QSize(70, 40));
    menu->setFixedSize(QSize(82, 40));
    back->setFixedSize(QSize(82, 40));

    // Volume logo is actually a hacky disabled button
    volumeLogo->setEnabled(false);
}


// -------------------------------------------------------------------------


void RemoteControl::setShortcuts()
{
    // Set shortcut keys for each button based on what is defined in the settings file
    up->setShortcut         (QKeySequence(Qt::Key_Up));
    down->setShortcut       (QKeySequence(Qt::Key_Down));
    left->setShortcut       (QKeySequence(Qt::Key_Left));
    right->setShortcut      (QKeySequence(Qt::Key_Right));
    enter->setShortcut      (QKeySequence(Qt::Key_Return));

    volumeUp->setShortcut   (QKeySequence(Qt::Key_BracketRight));
    volumeDown->setShortcut (QKeySequence(Qt::Key_BracketLeft));

    home->setShortcut       (QKeySequence(Qt::Key_M));
    previous->setShortcut   (QKeySequence(Qt::Key_Plus));
    stop->setShortcut       (QKeySequence(Qt::Key_X));
    playPause->setShortcut  (QKeySequence(Qt::Key_Space));
    next->setShortcut       (QKeySequence(Qt::Key_Minus));

    info->setShortcut       (QKeySequence(Qt::Key_N));
    menu->setShortcut       (QKeySequence(Qt::Key_R));
    back->setShortcut       (QKeySequence(Qt::Key_Backspace));

    // Set signal mapping for the buttons, the VALUES are defined in remotecontrol.h
    signalMapper->setMapping(up,         UP);
    signalMapper->setMapping(down,       DOWN);
    signalMapper->setMapping(left,       LEFT);
    signalMapper->setMapping(right,      RIGHT);
    signalMapper->setMapping(enter,      ENTER);

    signalMapper->setMapping(volumeUp,   VOLUME_UP);
    signalMapper->setMapping(volumeDown, VOLUME_DOWN);

    signalMapper->setMapping(home,       HOME);
    signalMapper->setMapping(previous,   PREVIOUS);
    signalMapper->setMapping(stop,       STOP);
    signalMapper->setMapping(playPause,  PLAY_PAUSE);
    signalMapper->setMapping(next,       NEXT);

    signalMapper->setMapping(info,       INFO);
    signalMapper->setMapping(menu,       MENU);
    signalMapper->setMapping(back,       BACK);

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(handleButton(int))) ;
}


// -------------------------------------------------------------------------


void RemoteControl::setUpLayout()
{
    QGridLayout *containerGrid  = new QGridLayout();
    QGridLayout *playerGrid     = new QGridLayout();
    QGridLayout *menuGrid       = new QGridLayout();

    containerGrid->setSpacing(5);
    playerGrid->setSpacing(5);
    menuGrid->setSpacing(5);

    containerGrid->setColumnMinimumWidth (1, 40);
    containerGrid->setColumnMinimumWidth (5, 40);

    containerGrid->setContentsMargins(8, 8, 8, 8);
    playerGrid->setContentsMargins   (0, 0, 0, 0);
    menuGrid->setContentsMargins     (0, 0, 0, 0);

    playerGrid->addWidget(home,          0, 0, Qt::AlignCenter);
    playerGrid->addWidget(previous,      0, 1, Qt::AlignCenter);
    playerGrid->addWidget(stop,          0, 2, Qt::AlignCenter);
    playerGrid->addWidget(playPause,     0, 3, Qt::AlignCenter);
    playerGrid->addWidget(next,          0, 4, Qt::AlignCenter);

    menuGrid->addWidget(info,            0, 1, Qt::AlignCenter);
    menuGrid->addWidget(menu,            0, 2, Qt::AlignCenter);
    menuGrid->addWidget(back,            0, 3, Qt::AlignCenter);

    containerGrid->addWidget(up,         0, 3, Qt::AlignCenter);
    containerGrid->addWidget(down,       2, 3, Qt::AlignCenter);
    containerGrid->addWidget(left,       1, 2, Qt::AlignCenter);
    containerGrid->addWidget(right,      1, 4, Qt::AlignCenter);
    containerGrid->addWidget(enter,      1, 3, Qt::AlignCenter);

    containerGrid->addWidget(volumeUp,   0, 6, Qt::AlignCenter);
    containerGrid->addWidget(volumeLogo, 1, 6, Qt::AlignCenter);
    containerGrid->addWidget(volumeDown, 2, 6, Qt::AlignCenter);

    containerGrid->addLayout(playerGrid,  0, 0, 1, 1); // rowNo, colNo, rowSpan, colSpan
    containerGrid->addLayout(menuGrid,    1, 0, 1, 1);

    setLayout(containerGrid);
}


// -------------------------------------------------------------------------


void RemoteControl::handleButton(int buttonCode)
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

    case PREVIOUS:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "skipprevious");
        json.insert("params", action);
        break;

    case STOP:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "stop");
        json.insert("params", action);
        break;

    case PLAY_PAUSE:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "pause");
        json.insert("params", action);
        break;

    case NEXT:
        json.insert("method", "Input.ExecuteAction");
        action.insert("action", "skipnext");
        json.insert("params", action);
        break;

    case BACK:
        json.insert("method", "Input.Back");
        break;

    default:
        json.insert("method", "Input.noop");
        break;
    }

    //QObject::connect(connection, &Connection::closed, this, &QCoreApplication::quit);

    connection->send(QJsonDocument(json));
    //connection->send(QString("{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"Input.Up\"}"));

    //connection->constructRequest(buttonCode);
}
