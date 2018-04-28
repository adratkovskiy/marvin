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
    trillianbody.cpp

HEADERS += \
        dialog.h \
    marvinbody.h \
    trillianbody.h

FORMS += \
        dialog.ui
