#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T12:36:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HWMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tindicator.cpp \
    tpanel.cpp \
    NetUDPClient.cpp \
    NetUDPClient_Linpack_Rustavi.cpp \
    NetUDPClient_Linpack.cpp \
    NetMonitor.cpp

HEADERS  += mainwindow.h \
    tindicator.h \
    tpanel.h \
    NetUDPClient.h \
    NetState.h \
    NetModule.h \
    NetDevice.h \
    NetCommand.h \
    HWPacket.h \
    NetUDPClient_Linpack.h \
    NetUDPClient_Linpack_Rustavi.h \
    NetMonitor.h \
    HWConnection.h \
    NetPacket.h

FORMS    += mainwindow.ui
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    images.qrc
