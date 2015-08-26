#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T10:31:29
#
#-------------------------------------------------

QT       += core

TARGET = KeySpy
TEMPLATE = app



# Warnings as errors - BEGIN
QMAKE_CFLAGS_WARN_ON   += -Werror
QMAKE_CXXFLAGS_WARN_ON += -Werror
# Warnings as errors - END

# Release optimization - BEGIN
QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -O3

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
# Release optimization - END



CONFIG += \
            warn_on \
            c++11

CONFIG (debug, debug|release) {
    DESTDIR = debug/
    OBJECTS_DIR = debug/gen
    MOC_DIR = debug/gen
    RCC_DIR = debug/gen
} else {
    DESTDIR = release/
    OBJECTS_DIR = release/gen
    MOC_DIR = release/gen
    RCC_DIR = release/gen
}



SOURCES += src/main.cpp
