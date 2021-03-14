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
    skipPrevious = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipBackward), QString());
    rewind       = new QPushButton(style()->standardIcon(QStyle::SP_MediaSeekBackward), QString());
    stop         = new QPushButton(style()->standardIcon(QStyle::SP_MediaStop), QString());
    playPause    = new QPushButton(style()->standardIcon(QStyle::SP_MediaPlay), QString());
    fastForward  = new QPushButton(style()->standardIcon(QStyle::SP_MediaSeekForward), QString());
    skipNext     = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipForward), QString());

    menu         = new QPushButton(QChar(0x2630));
    context      = new QPushButton(QChar(0x0043));
    info         = new QPushButton(QChar(0x24D8));
    back         = new QPushButton(QChar(0x21A9));

    up           = new QPushButton(QChar(0x2191));
    down         = new QPushButton(QChar(0x2193));
    left         = new QPushButton(QChar(0x2190));
    right        = new QPushButton(QChar(0x2192));
    enter        = new QPushButton(QString::fromUtf8("OK"));

    volumeUp     = new QPushButton(QChar(0x002B));
    volumeLogo   = new QPushButton(style()->standardIcon(QStyle::SP_MediaVolume), QString());
    volumeDown   = new QPushButton(QChar(0x2212));

    buttons << skipPrevious << rewind     << stop       << skipNext  << playPause
            << fastForward  << menu       << context    << info      << back
            << up           << down       << left       << right     << enter
            << volumeUp     << volumeLogo << volumeDown;

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
    QShortcut *stepBack        = new QShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Left), this);
    QShortcut *stepForward     = new QShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Right), this);
    QShortcut *mute            = new QShortcut(Qt::Key_Backslash, this);

    skipPrevious->setShortcut(Qt::Key_Minus);
    rewind->setShortcut      (Qt::Key_Comma);
    stop->setShortcut        (Qt::Key_X);
    playPause->setShortcut   (Qt::Key_Space);
    fastForward->setShortcut (Qt::Key_Period);
    skipNext->setShortcut    (Qt::Key_Equal);

    menu->setShortcut        (Qt::Key_M);
    context->setShortcut     (Qt::Key_C);
    info->setShortcut        (Qt::Key_I);
    back->setShortcut        (Qt::Key_Backspace);

    up->setShortcut          (Qt::Key_Up);
    down->setShortcut        (Qt::Key_Down);
    left->setShortcut        (Qt::Key_Left);
    right->setShortcut       (Qt::Key_Right);
    enter->setShortcut       (Qt::Key_Return);

    volumeUp->setShortcut    (Qt::Key_BracketRight);
    volumeDown->setShortcut  (Qt::Key_BracketLeft);

    // Set signal mapping for the buttons
    connect(skipPrevious,   &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("skipprevious"); });
    connect(bigStepBack,    &QShortcut::activated, m_connection, [=] { m_connection->sendExecuteActionMethod("bigstepback"); });
    connect(stepBack,       &QShortcut::activated, m_connection, [=] { m_connection->sendExecuteActionMethod("stepback"); });
    connect(rewind,         &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("rewind"); });
    connect(stop,           &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("stop"); });
    connect(playPause,      &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("pause"); });
    connect(fastForward,    &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("fastforward"); });
    connect(stepForward,    &QShortcut::activated, m_connection, [=] { m_connection->sendExecuteActionMethod("stepforward"); });
    connect(bigStepForward, &QShortcut::activated, m_connection, [=] { m_connection->sendExecuteActionMethod("bigstepforward"); });
    connect(skipNext,       &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("skipnext"); });

    connect(menu,           &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("ShowOSD"); });
    connect(context,        &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("contextmenu"); });
    connect(info,           &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("Info"); });
    connect(back,           &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("Back"); });

    connect(up,             &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("Up"); });
    connect(down,           &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("Down"); });
    connect(left,           &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("Left"); });
    connect(right,          &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("Right"); });
    connect(enter,          &QPushButton::clicked, m_connection, [=] { m_connection->sendInputDotMethod("Select"); });

    connect(volumeUp,       &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("volumeup"); });
    connect(volumeDown,     &QPushButton::clicked, m_connection, [=] { m_connection->sendExecuteActionMethod("volumedown"); });
    connect(mute,           &QShortcut::activated, m_connection, [=] { m_connection->sendExecuteActionMethod("mute"); });
}


void RemoteControl::setUpLayout()
{
    QGridLayout *grid = new QGridLayout();

    grid->setColumnMinimumWidth(6,  10);
    grid->setColumnMinimumWidth(10, 20);

    grid->setHorizontalSpacing(4);
    grid->setVerticalSpacing(8);

    grid->setMargin(8);

    grid->addWidget(menu,         1, 1,  Qt::AlignBottom);
    grid->addWidget(context,      1, 2,  Qt::AlignBottom);
    grid->addWidget(info,         1, 3,  Qt::AlignBottom);
    grid->addWidget(back,         1, 4,  Qt::AlignBottom);

    grid->addWidget(skipPrevious, 2, 0,  Qt::AlignTop);
    grid->addWidget(rewind,       2, 1,  Qt::AlignTop);
    grid->addWidget(stop,         2, 2,  Qt::AlignTop);
    grid->addWidget(playPause,    2, 3,  Qt::AlignTop);
    grid->addWidget(fastForward,  2, 4,  Qt::AlignTop);
    grid->addWidget(skipNext,     2, 5,  Qt::AlignTop);

    grid->addWidget(up,           0, 8,  Qt::AlignBottom);
    grid->addWidget(down,         2, 8,  Qt::AlignTop);
    grid->addWidget(left,         1, 7,  Qt::AlignRight);
    grid->addWidget(right,        1, 9,  Qt::AlignLeft);
    grid->addWidget(enter,        1, 8,  Qt::AlignCenter);

    grid->addWidget(volumeUp,     0, 11, Qt::AlignBottom);
    grid->addWidget(volumeLogo,   1, 11, Qt::AlignLeft);
    grid->addWidget(volumeDown,   2, 11, Qt::AlignTop);

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

        // The string we're after is 'value', which is inside 'data', which in turn is inside 'params'
        QString currentText = jsonObject.value("params").toObject().value("data").toObject().value("value").toString();

        if (m_debug) {qDebug() << "Received text input request to amend:" << currentText;}

        textInput->setText(currentText);
        openTextInput(true);
    }
}


void RemoteControl::sendText()
{
    m_connection->sendSendTextMethod(textInput->displayText());

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
    m_connection->sendInputDotMethod("Back");

    closeTextInput(true);
}
