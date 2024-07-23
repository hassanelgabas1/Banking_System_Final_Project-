QT -= gui
QT += network
CONFIG += console c++11
SOURCES += main.cpp \
           server.cpp
HEADERS += server.h
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
DISTFILES += \
    user_database.json \
    admin_database.json
