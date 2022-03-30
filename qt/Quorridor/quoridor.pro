QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boardgui.cpp \
    main.cpp \
    rankwidget.cpp \
    friendlistwidget.cpp \
    gamewindow.cpp \
    menuwindow.cpp \
    chatroom.cpp \
    friend.cpp \
    login.cpp \
    wallCell.cpp \
    wallsBox.cpp \
    pawncell.cpp

HEADERS += \
    boardgui.h \
    rankwidget.h \
    friendlistwidget.h \
    gamewindow.h \ 
    menuwindow.h \
    chatroom.h \
    friend.h \
    login.h \
    wallCell.h \
    wallsBox.h \
    pawncell.h
    

TRANSLATIONS += \
    Quorridor_fr_BE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    images.qrc

DISTFILES += \
    images/murH.jpg \
    images/murV.jpg \
    images/pion_blanc.png \
    images/pion_noir.png
