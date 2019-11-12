#-------------------------------------------------
#
# Project created by QtCreator 2019-10-10T23:05:50
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


SOURCES += \
        main.cpp \
        dht.cpp \
        pms.cpp \
        process.cpp \
    dialog.cpp \
    processthread.cpp

HEADERS += \
        dht.h \
        process.h \
        pms.h \
    dialog.h \
    processthread.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

INCLUDEPATH += $$PWD/../../../../../usr/lib/arm-linux-gnueabihf
DEPENDPATH += $$PWD/../../../../../usr/lib/arm-linux-gnueabihf
