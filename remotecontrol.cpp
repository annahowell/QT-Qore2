#include "remotecontrol.h"

RemoteControl::RemoteControl()
{
    connection = new Connection();

    createWidgets();
    setShortcuts();
    setUpLayout();
}


// -------------------------------------------------------------------------


void RemoteControl::createWidgets()
{
    // Create buttons
    up = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp), "");
    down = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown), "");
    left = new QPushButton(style()->standardIcon(QStyle::SP_ArrowLeft), "");
    right = new QPushButton(style()->standardIcon(QStyle::SP_ArrowRight), "");
    enter = new QPushButton(style()->standardIcon(QStyle::SP_DialogApplyButton), "");
    back = new QPushButton(style()->standardIcon(QStyle::SP_ArrowBack), "");

    volumeUp = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp), "");
    volumeLogo = new QPushButton(style()->standardIcon(QStyle::SP_MediaVolume), "");
    volumeDown = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown), "");

    stop = new QPushButton(style()->standardIcon(QStyle::SP_MediaStop), "");
    pause = new QPushButton(style()->standardIcon(QStyle::SP_MediaPause), "");
    play = new QPushButton(style()->standardIcon(QStyle::SP_MediaPlay), "");
    previous = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipBackward), "");
    rewind = new QPushButton(style()->standardIcon(QStyle::SP_MediaSeekBackward), "");
    fastForward = new QPushButton(style()->standardIcon(QStyle::SP_MediaSeekForward), "");
    next = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipForward), "");
    showOsd = new QPushButton(style()->standardIcon(QStyle::SP_FileDialogListView), "");

    sendText = new QLineEdit("");

    // Create array so we can foreach through adding default values for every button
    remote_buttons << up << down << left << right << enter << back << volumeUp << \
                      volumeLogo << volumeDown << stop << pause << play << previous << \
                      rewind << fastForward << next << showOsd;

    signalMapper = new QSignalMapper(this);

    for(auto& button : remote_buttons)
    {
      button->setFlat(false);
      button->setIconSize(QSize(52,52));
      connect (button, SIGNAL(clicked()), signalMapper, SLOT(map())) ;

    }

    // Volume logo is actually a hacky disabled button
    volumeLogo->setEnabled(false);

}


// -------------------------------------------------------------------------


void RemoteControl::setShortcuts()
{
    // Set shortcut keys for each button based on what is defined in the settings file
    up->setShortcut(QKeySequence(s.value("up").toString()));
    down->setShortcut(QKeySequence(s.value("down").toString()));
    left->setShortcut(QKeySequence(s.value("left").toString()));
    right->setShortcut(QKeySequence(s.value("right").toString()));
    enter->setShortcut(QKeySequence(s.value("enter").toString()));
    back->setShortcut(QKeySequence(s.value("back").toString()));

    volumeUp->setShortcut(QKeySequence(s.value("volumeup").toString()));
    volumeDown->setShortcut(QKeySequence(s.value("volumedown").toString()));

    stop->setShortcut(QKeySequence(s.value("stop").toString()));
    pause->setShortcut(QKeySequence(s.value("pause").toString()));
    previous->setShortcut(QKeySequence(s.value("previous").toString()));
    rewind->setShortcut(QKeySequence(s.value("rewind").toString()));
    fastForward->setShortcut(QKeySequence(s.value("fastforward").toString()));
    next->setShortcut(QKeySequence(s.value("next").toString()));
    showOsd->setShortcut(QKeySequence(s.value("showosd").toString()));

    // Set signal mapping for the buttons, the VALUES are defined in connection.h
    // Navigation buttons
    signalMapper->setMapping(up, UP);
    signalMapper->setMapping(down, DOWN);
    signalMapper->setMapping(left, LEFT);
    signalMapper->setMapping(right, RIGHT);
    signalMapper->setMapping(enter, ENTER);
    signalMapper->setMapping(back, BACK);

    //Volume buttons
    signalMapper->setMapping(volumeUp, VOLUME_UP);
    signalMapper->setMapping(volumeDown, VOLUME_DOWN);

    // Player buttons
    signalMapper->setMapping(stop, STOP);
    signalMapper->setMapping(pause, PAUSE);
    signalMapper->setMapping(play, PLAY);
    signalMapper->setMapping(previous, PREVIOUS);
    signalMapper->setMapping(rewind, REWIND);
    signalMapper->setMapping(fastForward, FAST_FORWARD);
    signalMapper->setMapping(next, NEXT);
    signalMapper->setMapping(showOsd, SHOW_OSD);

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(handleButton(int))) ;
}


// -------------------------------------------------------------------------


void RemoteControl::setUpLayout()
{
    // Create window, relevant grids and add buttons etc
    QGridLayout *grid = new QGridLayout;

    // Add navigation buttons to window
    grid->addWidget(up, 0, 1);
    grid->addWidget(down, 2, 1);
    grid->addWidget(left, 1, 0);
    grid->addWidget(right, 1, 2);
    grid->addWidget(enter, 1, 1);
    grid->addWidget(back, 2, 0);

    // Add volume buttons to window
    grid->addWidget(volumeUp, 0, 4);
    grid->addWidget(volumeLogo, 1, 4);
    grid->addWidget(volumeDown, 2, 4);

    // Create grid for player buttons and add widgets
    QGridLayout *playerGrid = new QGridLayout();
    playerGrid->setContentsMargins(0, 40, 0, 0);

    grid->addLayout(playerGrid, 3, 0, 1, 5);

    playerGrid->addWidget(stop, 3, 1);
    playerGrid->addWidget(pause, 3, 2);
    playerGrid->addWidget(play, 3, 3);

    playerGrid->addWidget(previous, 4, 0);
    playerGrid->addWidget(rewind, 4, 1);
    playerGrid->addWidget(fastForward, 4, 2);
    playerGrid->addWidget(next, 4, 3);
    playerGrid->addWidget(showOsd, 4, 4);


    // Create grid for text sender and add widgets
    QGridLayout *textGrid = new QGridLayout();
    textGrid->setContentsMargins(0, 32, 0, 0);
    textGrid->addWidget(sendText, 0, 0);
    grid->addLayout(textGrid, 5, 0, 1, 4);

    setLayout(grid);
}


// -------------------------------------------------------------------------


void RemoteControl::handleButton(int buttonCode)
{
    connection->constructRequest(buttonCode);
}
