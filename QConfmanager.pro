#-------------------------------------------------
#
# Project created by QtCreator 2019-10-16T08:41:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QConfmanager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RC_ICONS = rc/icon.ico

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    contenprovider.cpp \
    custombutton.cpp \
    customlayout.cpp \
        main.cpp \
        mainwindow.cpp \
    gui.cpp \
    room.cpp \
    asterisk.cpp \
    notification.cpp \
    settings.cpp

HEADERS += \
    contenprovider.h \
    custombutton.h \
    customlayout.h \
        mainwindow.h \
    gui.h \
    room.h \
    asterisk.h \
    notification.h \
    settings.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    rc/icon.png \
    rc/icon.svg

RESOURCES += \
    icons.qrc
