QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11 

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
    ../Quorridor/View/Interface/pawncell.h

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
