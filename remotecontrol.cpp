#include "remotecontrol.h"

RemoteControl::RemoteControl()
{
    connection = new Connection(QUrl(QStringLiteral("ws://127.0.0.1:9090")), true);

    createWidgets();
    setShortcuts();
    setUpLayout();
}


// -------------------------------------------------------------------------


void RemoteControl::createWidgets()
{
    // Create buttons
    up          = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp), "");
    down        = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown), "");
    left        = new QPushButton(style()->standardIcon(QStyle::SP_ArrowLeft), "");
    right       = new QPushButton(style()->standardIcon(QStyle::SP_ArrowRight), "");
    enter       = new QPushButton(style()->standardIcon(QStyle::SP_DialogApplyButton), "");

    volumeUp    = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp), "");
    volumeLogo  = new QPushButton(style()->standardIcon(QStyle::SP_MediaVolume), "");
    volumeDown  = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown), "");

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
      button->setFixedSize(QSize(40, 40));
      button->setFlat(false);
      button->setIconSize(QSize(20,20));
      connect (button, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
    }

    // Now set the non-square buttons
    home->setFixedSize(80, 40);
    info->setFixedSize(66, 40);
    menu->setFixedSize(80, 40);
    back->setFixedSize(80, 40);

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

    // Create container grid to hold the playerGrid, controlGrid and volumeGrid
    QGridLayout *containerGrid = new QGridLayout;
    containerGrid->setSpacing(5);
    containerGrid->setContentsMargins(8, 8, 8, 8);

    // Create grid for player buttons and add widgets
    QGridLayout *playerMenusContainerGrid = new QGridLayout();
    playerMenusContainerGrid->setSpacing(5);

    // Create grid for player buttons and add widgets
    QGridLayout *playerGrid = new QGridLayout();
    playerGrid->setSpacing(5);

    playerGrid->addWidget(home,      0, 0);
    playerGrid->addWidget(previous,  0, 1);
    playerGrid->addWidget(stop,      0, 2);
    playerGrid->addWidget(playPause, 0, 3);
    playerGrid->addWidget(next,      0, 4);

    // Create grid for player buttons and add widgets
    QGridLayout *menuGrid = new QGridLayout();
    menuGrid->setSpacing(5);

    menuGrid->addWidget(info,      0, 1);
    menuGrid->addWidget(menu,      0, 2);
    menuGrid->addWidget(back,      0, 3);

    playerMenusContainerGrid->addLayout(playerGrid, 1, 0, 2, 1);
    playerMenusContainerGrid->addLayout(menuGrid, 2, 0, 1, 1);

    containerGrid->addLayout(playerMenusContainerGrid, 0, 0, 1, 1);


    // Add navigation buttons to window
    QGridLayout *controlGrid = new QGridLayout;
    //controlGrid->setSpacing(5);
    controlGrid->setContentsMargins(24, 0, 0, 0);

    controlGrid->addWidget(up,         0, 1);
    controlGrid->addWidget(down,       2, 1);
    controlGrid->addWidget(left,       1, 0);
    controlGrid->addWidget(right,      1, 2);
    controlGrid->addWidget(enter,      1, 1);

    containerGrid->addLayout(controlGrid, 0, 1, 1, 1);


    // Add volume buttons to window
    QGridLayout *volumeGrid = new QGridLayout;
    volumeGrid->setSpacing(5);
    volumeGrid->setContentsMargins(24, 0, 0, 0);

    volumeGrid->addWidget(volumeUp,   0, 4);
    volumeGrid->addWidget(volumeLogo, 1, 4);
    volumeGrid->addWidget(volumeDown, 2, 4);

    containerGrid->addLayout(volumeGrid, 0, 2, 1, 1);





    // Create grid for text sender and add widgets
    //QGridLayout *textGrid = new QGridLayout();
    //textGrid->setContentsMargins(0, 32, 0, 0);
    //textGrid->addWidget(sendText, 0, 0);
    //grid->addLayout(textGrid, 5, 0, 1, 4);

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
