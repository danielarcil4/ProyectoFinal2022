QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basicobject.cpp \
    basicsign.cpp \
    bird.cpp \
    finishline.cpp \
    main.cpp \
    mainwindow.cpp \
    marsh.cpp \
    ownclock.cpp \
    player.cpp \
    point.cpp \
    score.cpp \
    scorpion.cpp \
    solidblock.cpp

HEADERS += \
    basicobject.h \
    basicsign.h \
    bird.h \
    finishline.h \
    mainwindow.h \
    marsh.h \
    ownclock.h \
    player.h \
    point.h \
    score.h \
    scorpion.h \
    solidblock.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sprites.qrc
