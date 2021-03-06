#include "remotecontrol.h"

RemoteControl::RemoteControl(Connection *connection)
    : m_connection(connection)
{
    createWidgets();
    setShortcuts();
    setUpLayout();
}

void RemoteControl::createWidgets()
{
    previous    = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipBackward), QString());
    rewind      = new QPushButton(style()->standardIcon(QStyle::SP_MediaSeekBackward), QString());
    stop        = new QPushButton(style()->standardIcon(QStyle::SP_MediaStop), QString());
    playPause   = new QPushButton(style()->standardIcon(QStyle::SP_MediaPlay), QString());
    fastForward = new QPushButton(style()->standardIcon(QStyle::SP_MediaSeekForward), QString());
    next        = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipForward), QString());

    menu        = new QPushButton(QChar(0x2630));
    context     = new QPushButton(QChar(0x0043));
    info        = new QPushButton(QChar(0x24D8));
    back        = new QPushButton(QChar(0x21A9));

    up          = new QPushButton(QChar(0x2191));
    down        = new QPushButton(QChar(0x2193));
    left        = new QPushButton(QChar(0x2190));
    right       = new QPushButton(QChar(0x2192));
    enter       = new QPushButton(QString::fromUtf8("OK"));

    volumeUp    = new QPushButton(QChar(0x002B));
    volumeLogo  = new QPushButton(style()->standardIcon(QStyle::SP_MediaVolume), QString());
    volumeDown  = new QPushButton(QChar(0x2212));

    buttons << previous << rewind << stop         << next << playPause << fastForward
            << menu     << context  << info       << back
            << up       << down     << left       << right
            << enter    << volumeUp << volumeLogo << volumeDown;

    signalMapper = new QSignalMapper();

    for(auto& button : buttons)
    {
      button->setFixedSize(QSize(42, 40));
      button->setFlat(false);
      connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
    }

    // Volume logo is actually a hacky disabled button
    volumeLogo->setEnabled(false);
}


void RemoteControl::setShortcuts()
{
    QShortcut *bigStepBackward = new QShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Down), this);
    QShortcut *bigStepForward  = new QShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Up), this);
    connect(bigStepBackward, SIGNAL(activated()), signalMapper, SLOT(map()));
    connect(bigStepForward, SIGNAL(activated()), signalMapper, SLOT(map()));

    previous->setShortcut   (QKeySequence(Qt::Key_Minus));
    rewind->setShortcut     (QKeySequence(Qt::ShiftModifier + Qt::Key_Left));
    stop->setShortcut       (QKeySequence(Qt::Key_X));
    playPause->setShortcut  (QKeySequence(Qt::Key_Space));
    fastForward->setShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Right));
    next->setShortcut       (QKeySequence(Qt::Key_Equal));

    menu->setShortcut       (QKeySequence(Qt::Key_M));
    context->setShortcut    (QKeySequence(Qt::Key_C));
    info->setShortcut       (QKeySequence(Qt::Key_I));
    back->setShortcut       (QKeySequence(Qt::Key_Backspace));

    up->setShortcut         (QKeySequence(Qt::Key_Up));
    down->setShortcut       (QKeySequence(Qt::Key_Down));
    left->setShortcut       (QKeySequence(Qt::Key_Left));
    right->setShortcut      (QKeySequence(Qt::Key_Right));
    enter->setShortcut      (QKeySequence(Qt::Key_Return));

    volumeUp->setShortcut   (QKeySequence(Qt::Key_BracketRight));
    volumeDown->setShortcut (QKeySequence(Qt::Key_BracketLeft));

    // Set signal mapping for the buttons
    signalMapper->setMapping(previous,        PREVIOUS);
    signalMapper->setMapping(bigStepBackward, BIG_STEP_BACK);
    signalMapper->setMapping(rewind,          REWIND);
    signalMapper->setMapping(stop,            STOP);
    signalMapper->setMapping(playPause,       PLAY_PAUSE);
    signalMapper->setMapping(fastForward,     FAST_FORWARD);
    signalMapper->setMapping(bigStepForward,  BIG_STEP_FORWARD);
    signalMapper->setMapping(next,            NEXT);

    signalMapper->setMapping(menu,            MENU);
    signalMapper->setMapping(context,         CONTEXT);
    signalMapper->setMapping(info,            INFO);
    signalMapper->setMapping(back,            BACK);

    signalMapper->setMapping(up,              UP);
    signalMapper->setMapping(down,            DOWN);
    signalMapper->setMapping(left,            LEFT);
    signalMapper->setMapping(right,           RIGHT);
    signalMapper->setMapping(enter,           ENTER);

    signalMapper->setMapping(volumeUp,        VOLUME_UP);
    signalMapper->setMapping(volumeDown,      VOLUME_DOWN);


    connect(signalMapper, &QSignalMapper::mappedInt, this, &RemoteControl::handleRemote);
}


void RemoteControl::setUpLayout()
{
    QGridLayout *grid = new QGridLayout();

    grid->setColumnMinimumWidth (6,  10);
    grid->setColumnMinimumWidth (10, 20);

    grid->setHorizontalSpacing(4);
    grid->setVerticalSpacing(8);

    grid->setMargin(8);

    grid->addWidget(menu,        1, 1,  Qt::AlignBottom);
    grid->addWidget(context,     1, 2,  Qt::AlignBottom);
    grid->addWidget(info,        1, 3,  Qt::AlignBottom);
    grid->addWidget(back,        1, 4,  Qt::AlignBottom);

    grid->addWidget(previous,    2, 0,  Qt::AlignTop);
    grid->addWidget(rewind,      2, 1,  Qt::AlignTop);
    grid->addWidget(stop,        2, 2,  Qt::AlignTop);
    grid->addWidget(playPause,   2, 3,  Qt::AlignTop);
    grid->addWidget(fastForward, 2, 4,  Qt::AlignTop);
    grid->addWidget(next,        2, 5,  Qt::AlignTop);

    grid->addWidget(up,          0, 8,  Qt::AlignBottom);
    grid->addWidget(down,        2, 8,  Qt::AlignTop);
    grid->addWidget(left,        1, 7,  Qt::AlignRight);
    grid->addWidget(right,       1, 9,  Qt::AlignLeft);
    grid->addWidget(enter,       1, 8,  Qt::AlignCenter);

    grid->addWidget(volumeUp,    0, 11, Qt::AlignBottom);
    grid->addWidget(volumeLogo,  1, 11, Qt::AlignLeft);
    grid->addWidget(volumeDown,  2, 11, Qt::AlignTop);

    setLayout(grid);
}

void RemoteControl::handleRemote(int code)
{
    QJsonObject action;
    QJsonObject json
    {
        {"jsonrpc", "2.0"},
        {"id", "1"}
    };

    switch (code) {
        case PREVIOUS:
            json.insert("method", "Input.ExecuteAction");
            action.insert("action", "skipprevious");
            json.insert("params", action);
            break;

        case BIG_STEP_BACK:
            json.insert("method", "Input.ExecuteAction");
            action.insert("action", "bigstepback");
            json.insert("params", action);
            break;

        case REWIND:
            json.insert("method", "Input.ExecuteAction");
            action.insert("action", "stepback");
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

        case FAST_FORWARD:
            json.insert("method", "Input.ExecuteAction");
            action.insert("action", "stepforward");
            json.insert("params", action);
            break;

        case BIG_STEP_FORWARD:
            json.insert("method", "Input.ExecuteAction");
            action.insert("action", "bigstepforward");
            json.insert("params", action);
            break;

        case NEXT:
            json.insert("method", "Input.ExecuteAction");
            action.insert("action", "skipnext");
            json.insert("params", action);
            break;

        case MENU:
            json.insert("method", "Input.ShowOSD");
            break;

        case CONTEXT:
            json.insert("method", "Input.ExecuteAction");
            action.insert("action", "contextmenu");
            json.insert("params", action);
            break;

        case INFO:
            json.insert("method", "Input.Info");
            break;

        case BACK:
            json.insert("method", "Input.Back");
            break;

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

        default:
            json.insert("method", "Input.noop");
            break;
    }

    qDebug() << json;

    m_connection->send(QJsonDocument(json));
}
