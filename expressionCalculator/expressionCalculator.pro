TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fraction.cpp \
    term.cpp \
    mixednumber.cpp \
    polynomial.cpp \
    parser.cpp \
    expressioncalculator.cpp

HEADERS += \
    expressioncalculator.h \
    fraction.h \
    term.h \
    mixednumber.h \
    polynomial.h \
    parser.h
