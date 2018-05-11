#-------------------------------------------------
#
# Project created by QtCreator 2018-04-28T12:27:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = marvin
TEMPLATE = app


SOURCES += \
        main.cpp \
        dialog.cpp \
    marvinbody.cpp \
    trillianbody.cpp \
    eye.cpp \
    marvinhand.cpp

HEADERS += \
        dialog.h \
    marvinbody.h \
    trillianbody.h \
    eye.h \
    marvinhand.h

FORMS += \
        dialog.ui

INCLUDEPATH += /usr/include /usr/local/include
LIBS += -L/usr/local/lib -lbcm2835
