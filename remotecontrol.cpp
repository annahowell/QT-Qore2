#include "remotecontrol.h"

RemoteControl::RemoteControl(Connection *connection) : m_connection(connection)
{
//    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

    //createWidgets();
    //setShortcuts();
    //setUpLayout();

    tabs = new QTabWidget(this);
    tabs->setFixedSize(490, 154);

    //tabs->addTab(remoteControl, QString::fromUtf8("Remote"));
    //tabs->addTab(settings, QString::fromUtf8("Settings"));
    tabs->addTab(RemoteControl::handleQuit(), QString::fromUtf8("Quit"));

    setWindowTitle(QString::fromUtf8("Qore2"));
    setFixedSize(490, 154);

    show();
    raise();
    setFocus();
    activateWindow();
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

    signalMapper = new QSignalMapper(this);

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
    signalMapper->setMapping(previous,    PREVIOUS);
    signalMapper->setMapping(rewind,      REWIND);
    signalMapper->setMapping(stop,        STOP);
    signalMapper->setMapping(playPause,   PLAY_PAUSE);
    signalMapper->setMapping(fastForward, FAST_FORWARD);
    signalMapper->setMapping(next,        NEXT);

    signalMapper->setMapping(menu,        MENU);
    signalMapper->setMapping(context,     CONTEXT);
    signalMapper->setMapping(info,        INFO);
    signalMapper->setMapping(back,        BACK);

    signalMapper->setMapping(up,          UP);
    signalMapper->setMapping(down,        DOWN);
    signalMapper->setMapping(left,        LEFT);
    signalMapper->setMapping(right,       RIGHT);
    signalMapper->setMapping(enter,       ENTER);

    signalMapper->setMapping(volumeUp,    VOLUME_UP);
    signalMapper->setMapping(volumeDown,  VOLUME_DOWN);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(handleButton(int)));
}


void RemoteControl::setUpLayout()
{
    QGridLayout *containerGrid = new QGridLayout();

    containerGrid->setColumnMinimumWidth (6,  10);
    containerGrid->setColumnMinimumWidth (10, 20);

    containerGrid->setHorizontalSpacing(4);
    containerGrid->setVerticalSpacing(8);

    containerGrid->setMargin(8);

    containerGrid->addWidget(menu,        1, 1,  Qt::AlignBottom);
    containerGrid->addWidget(context,     1, 2,  Qt::AlignBottom);
    containerGrid->addWidget(info,        1, 3,  Qt::AlignBottom);
    containerGrid->addWidget(back,        1, 4,  Qt::AlignBottom);

    containerGrid->addWidget(previous,    2, 0,  Qt::AlignTop);
    containerGrid->addWidget(rewind,      2, 1,  Qt::AlignTop);
    containerGrid->addWidget(stop,        2, 2,  Qt::AlignTop);
    containerGrid->addWidget(playPause,   2, 3,  Qt::AlignTop);
    containerGrid->addWidget(fastForward, 2, 4,  Qt::AlignTop);
    containerGrid->addWidget(next,        2, 5,  Qt::AlignTop);

    containerGrid->addWidget(up,          0, 8,  Qt::AlignBottom);
    containerGrid->addWidget(down,        2, 8,  Qt::AlignTop);
    containerGrid->addWidget(left,        1, 7,  Qt::AlignRight);
    containerGrid->addWidget(right,       1, 9,  Qt::AlignLeft);
    containerGrid->addWidget(enter,       1, 8,  Qt::AlignCenter);

    containerGrid->addWidget(volumeUp,    0, 11, Qt::AlignBottom);
    containerGrid->addWidget(volumeLogo,  1, 11, Qt::AlignLeft);
    containerGrid->addWidget(volumeDown,  2, 11, Qt::AlignTop);

    setLayout(containerGrid);
}

void RemoteControl::closeEvent(QCloseEvent *event)
{


    event->ignore();

    this->destroy();
}

void RemoteControl::handleButton(int buttonCode)
{
    QJsonObject action;
    QJsonObject json
    {
        {"jsonrpc", "2.0"},
        {"id", "1"}
    };

    switch (buttonCode) {
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

    m_connection->send(QJsonDocument(json));
}

QWidget* RemoteControl::handleQuit()
{
    QWidget *quitWidget = new QWidget();
    quitGrid            = new QGridLayout();

    confirmMsg   = new QLabel(tr("Are you sure you wish to quit?"));
    cancelButton = new QPushButton("Cancel");
    quitButton   = new QPushButton("Ok");

    cancelButton->setFixedWidth(100);
    quitButton->setFixedWidth(100);

    quitGrid->setHorizontalSpacing(4);
    quitGrid->setVerticalSpacing(8);

    quitGrid->setColumnMinimumWidth(0, 50);
    quitGrid->setColumnMinimumWidth(2, 20);
    quitGrid->setColumnMinimumWidth(4, 50);

    quitGrid->addWidget(confirmMsg,   0, 1, 1, 3, Qt::AlignCenter); //row col rowSpan colSpan
    quitGrid->addWidget(cancelButton, 1, 1, 1, 1, Qt::AlignCenter);
    quitGrid->addWidget(quitButton,   1, 3, 1, 1, Qt::AlignCenter);

    connect(quitButton,   &QPushButton::clicked, this, &QApplication::quit);
    connect(cancelButton, &QPushButton::clicked, this, [this]{
        tabs->setCurrentIndex(0);
    });

    quitWidget->setLayout(quitGrid);

    return quitWidget;
}
