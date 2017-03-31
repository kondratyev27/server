TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -pthread

SOURCES += main.cpp \
    server.cpp \
    tcpserver.cpp \
    udpserver.cpp

HEADERS += \
    server.h \
    tcpserver.h \
    udpserver.h

