#include "remotecontrol.h"

RemoteControl::RemoteControl(bool debug, Connection *connection)
    : m_debug(debug), m_connection(connection)
{
    textInputShouldBeOpen = false;

    createWidgets();
    setShortcutsAndBindings();
    setUpLayout();
    setUpTextInput();

    connect(m_connection, &QWebSocket::textMessageReceived, this, &RemoteControl::onTextMessageReceived);
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

    buttons << previous    << rewind     << stop       << next  << playPause
            << fastForward << menu       << context    << info  << back
            << up          << down       << left       << right << enter
            << volumeUp    << volumeLogo << volumeDown;

    for(auto& button : buttons)
    {
      button->setFixedSize(QSize(42, 40));
      button->setFlat(false);
    }

    // Volume logo is just a hacky disabled button
    volumeLogo->setEnabled(false);
}


void RemoteControl::setShortcutsAndBindings()
{
    QShortcut *bigStepBack     = new QShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Down), this);
    QShortcut *bigStepForward  = new QShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Up), this);

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
    connect(previous,       &QPushButton::clicked, m_connection, [this] { handleRemote(PREVIOUS); });
    connect(bigStepBack,    &QShortcut::activated, m_connection, [this] { handleRemote(BIG_STEP_BACK); });
    connect(rewind,         &QPushButton::clicked, m_connection, [this] { handleRemote(REWIND); });
    connect(stop,           &QPushButton::clicked, m_connection, [this] { handleRemote(STOP); });
    connect(playPause,      &QPushButton::clicked, m_connection, [this] { handleRemote(PLAY_PAUSE); });
    connect(fastForward,    &QPushButton::clicked, m_connection, [this] { handleRemote(FAST_FORWARD); });
    connect(bigStepForward, &QShortcut::activated, m_connection, [this] { handleRemote(BIG_STEP_FORWARD); });
    connect(next,           &QPushButton::clicked, m_connection, [this] { handleRemote(NEXT); });

    connect(menu,           &QPushButton::clicked, m_connection, [this] { handleRemote(MENU); });
    connect(context,        &QPushButton::clicked, m_connection, [this] { handleRemote(CONTEXT); });
    connect(info,           &QPushButton::clicked, m_connection, [this] { handleRemote(INFO); });
    connect(back,           &QPushButton::clicked, m_connection, [this] { handleRemote(BACK); });

    connect(up,             &QPushButton::clicked, m_connection, [this] { handleRemote(UP); });
    connect(down,           &QPushButton::clicked, m_connection, [this] { handleRemote(DOWN); });
    connect(left,           &QPushButton::clicked, m_connection, [this] { handleRemote(LEFT); });
    connect(right,          &QPushButton::clicked, m_connection, [this] { handleRemote(RIGHT); });
    connect(enter,          &QPushButton::clicked, m_connection, [this] { handleRemote(ENTER); });

    connect(volumeUp,       &QPushButton::clicked, m_connection, [this] { handleRemote(VOLUME_UP); });
    connect(volumeDown,     &QPushButton::clicked, m_connection, [this] { handleRemote(VOLUME_DOWN); });
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


void RemoteControl::setUpTextInput()
{
    textInputDialog = new QDialog(this, Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    textInputDialog->setFixedSize(400, 60);

    QVBoxLayout *textInputLayout = new QVBoxLayout();
    textInput = new QLineEdit();
    textInputLayout->addWidget(textInput);

    textInputDialog->setLayout(textInputLayout);

    connect(textInput, &QLineEdit::returnPressed, this, &RemoteControl::sendText);
    connect(textInputDialog, &QDialog::rejected, this, &RemoteControl::cancelSendText);
}


void RemoteControl::handleRemote(int code)
{
    QJsonObject params;
    QJsonObject json {
        {"jsonrpc", "2.0"},
        {"id", "1"},
        {"method", "Input.ExecuteAction"} // Method may get overwritten below
    };

    switch (code) {
        case PREVIOUS:
            params.insert("action", "skipprevious");
            break;

        case BIG_STEP_BACK:
            params.insert("action", "bigstepback");
            break;

        case REWIND:
            params.insert("action", "stepback");
            break;

        case STOP:
            params.insert("action", "stop");
            break;

        case PLAY_PAUSE:
            params.insert("action", "pause");
            break;

        case FAST_FORWARD:
            params.insert("action", "stepforward");
            break;

        case BIG_STEP_FORWARD:
            params.insert("action", "bigstepforward");
            break;

        case NEXT:
            params.insert("action", "skipnext");
            break;

        case MENU:
            json.insert("method", "Input.ShowOSD");
            break;

        case CONTEXT:
            params.insert("action", "contextmenu");
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
            params.insert("action", "volumedown");
            break;

        case VOLUME_UP:
            params.insert("action", "volumeup");
            break;
    }

    if (!params.empty()) {
        json.insert("params", params);
    }

    m_connection->send(QJsonDocument(json));
}


bool RemoteControl::getTextInputShouldBeOpen()
{
    return textInputShouldBeOpen;
}


void RemoteControl::onTextMessageReceived(const QString &frame)
{
    if (m_debug) {qDebug() << "Received message: " << frame;}

    QJsonObject jsonObject = QJsonDocument::fromJson(frame.toUtf8()).object();
    QString method = jsonObject.value("method").toString();

    // If the method wants an input
    if (QString::compare(method, "Input.OnInputRequested", Qt::CaseInsensitive) == 0) {
        textInputDialog->close();

        // The string we're after is value, which is inside data, which in turn is inside params
        QString currentText = jsonObject.value("params").toObject().value("data").toObject().value("value").toString();

        if (m_debug) {qDebug() << "Received text input request to amend:" << currentText;}

        textInput->setText(currentText);
        openTextInput(true);
    }
}


void RemoteControl::sendText()
{
    QJsonObject json {
        {"jsonrpc", "2.0"},
        {"method", "Input.SendText"},
        {"params", QJsonObject {
                {"text", textInput->displayText()}
            }
        },
        {"id", "1"}
    };

    m_connection->send(QJsonDocument(json));

    closeTextInput(true);
}


void RemoteControl::openTextInput(bool updateShouldBeOpenBool)
{
    textInputShouldBeOpen = updateShouldBeOpenBool ? true : textInputShouldBeOpen;

    textInputDialog->show();
    textInputDialog->activateWindow();
    textInputDialog->raise();

    textInput->setFocus();
}


void RemoteControl::closeTextInput(bool updateShouldBeOpenBool)
{
    textInputDialog->hide();

    if (updateShouldBeOpenBool) {
        textInput->setText("");
        textInputShouldBeOpen = false;
    }
}


void RemoteControl::cancelSendText()
{
    // If the user has canceled we'll send Input.Back to the API to close the Kodi window and close the text input popup
    handleRemote(BACK);

    closeTextInput(true);
}
