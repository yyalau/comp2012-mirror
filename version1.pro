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
    _setup.cpp \
    bulletBase.cpp \
    bulletEnemy.cpp \
    bulletPlayer.cpp \
    bulletPowerUp.cpp \
    customTimer.cpp \
    gameEvent.cpp \
    health.cpp \
    infoBox.cpp \
    main.cpp \
    popUpDialogue.cpp \
    shooterBase.cpp \
    shooterBoss.cpp \
    shooterEnemy.cpp \
    shooterPlayer.cpp

HEADERS += \
    _setup.h \
    bulletBase.h \
    bulletEnemy.h \
    bulletPlayer.h \
    bulletPowerUp.h \
    customTimer.h \
    define.h \
    gameEvent.h \
    health.h \
    infoBox.h \
    popUpDialogue.h \
    shooterBase.h \
    shooterBoss.h \
    shooterEnemy.h \
    shooterPlayer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
