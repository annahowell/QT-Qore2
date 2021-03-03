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

CONFIG   += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = qore2
TEMPLATE  = app


SOURCES  += main.cpp\
            mainwindow.cpp \
            connection.cpp \
            remotecontrol.cpp \
            settings.cpp

HEADERS  += mainwindow.h \
            connection.h \
            remotecontrol.h \
            settings.h

RESOURCES += \
    resources.qrc

QMAKE_INFO_PLIST = Info.plist

DISTFILES += \
    README.md \
    Info.plist
