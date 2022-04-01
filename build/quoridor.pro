QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS+=-lncursesw -pthread 

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    ../Quorridor/View/Interface/boardgui.cpp \
    ../Quorridor/View/Interface/main.cpp \
    ../Quorridor/View/Interface/rankwidget.cpp \
    ../Quorridor/View/Interface/friendlistwidget.cpp \
    ../Quorridor/View/Interface/gamewindow.cpp \
    ../Quorridor/View/Interface/menuwindow.cpp \
    ../Quorridor/View/Interface/chatroom.cpp \
    ../Quorridor/View/Interface/friend.cpp \
    ../Quorridor/View/Interface/login.cpp \
    ../Quorridor/View/Interface/wallCell.cpp \
    ../Quorridor/View/Interface/wallsBox.cpp \
    ../Quorridor/View/Interface/pawncell.cpp \
    ../ServerClient/client.cpp \
    ../ServerClient/socketlib.cpp

HEADERS += \
    ../Quorridor/View/Interface/boardgui.h \
    ../Quorridor/View/Interface/rankwidget.h \
    ../Quorridor/View/Interface/friendlistwidget.h \
    ../Quorridor/View/Interface/gamewindow.h \  \
    ../Quorridor/View/Interface/menuwindow.h \
    ../Quorridor/View/Interface/chatroom.h \
    ../Quorridor/View/Interface/friend.h \
    ../Quorridor/View/Interface/login.h \
    ../Quorridor/View/Interface/wallCell.h \
    ../Quorridor/View/Interface/wallsBox.h \
    ../Quorridor/View/Interface/pawncell.h \
    ../ServerClient/WindowNC.hpp \
    ../ServerClient/client.h \
    ../ServerClient/socketlib.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    ../Quorridor/View/Interface/images.qrc

DISTFILES += \
    ../Quorridor/View/Interface/images/murH.jpg \
    ../Quorridor/View/Interface/images/murV.jpg \
    ../Quorridor/View/Interface/images/pion_blanc.png \
    ../Quorridor/View/Interface/images/pion_noir.png \
    ../ServerClient/socketlib.o
