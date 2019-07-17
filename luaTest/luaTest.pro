TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -llua -ldl /usr/lib/x86_64-linux-gnu/liblua5.3.so

SOURCES += main.cpp \
    scripter.cpp

HEADERS += \
    scripter.h
