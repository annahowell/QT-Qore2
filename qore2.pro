#-------------------------------------------------
#
# Project created by QtCreator 2017-10-06T10:30:04
#
#-------------------------------------------------

include(vendor/vendor.pri)


QT       += core gui
QT       += network
QT       += widgets
QT       += websockets

CONFIG   += C++11 app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = Qore2
TEMPLATE  = app

RC_ICONS  = Qore2.ico
ICON      = Qore2.icns

HEADERS  += mainwindow.h \
            connection.h \
            remotecontrol.h \
            settings.h \
            trayapp.h

SOURCES  += main.cpp\
            mainwindow.cpp \
            connection.cpp \
            remotecontrol.cpp \
            settings.cpp \
            trayapp.cpp

RESOURCES += \
    resources.qrc

QMAKE_INFO_PLIST = Info.plist

DISTFILES += \
    README.md \
    Info.plist
