TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        file_converter.cpp \
        main.cpp \
        steganography.cpp

HEADERS += \
    bmp.h \
    file_converter.h \
    steganography.h
