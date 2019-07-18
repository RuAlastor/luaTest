TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -llua -ldl -Wl,-E

#LIBS += /usr/lib/x86_64-linux-gnu/liblua5.3.so
# equales
#LIBS += -Wl,-E

SOURCES += main.cpp \
    scripter.cpp

HEADERS += \
    scripter.h

DISTFILES += \
    ../../../lua/sqltest.lua \
    ../../../lua/tabletest.lua
