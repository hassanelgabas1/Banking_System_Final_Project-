QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    client.cpp

HEADERS += \
    loginwindow.h \
    mainwindow.h \
    client.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
