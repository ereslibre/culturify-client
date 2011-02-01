#-------------------------------------------------
#
# Project created by QtCreator 2011-01-29T17:25:38
#
#-------------------------------------------------

QT          += core gui network

INCLUDEPATH += /usr/include/mongo

LIBS += -lqjson \
        -lmongoclient \
        -lboost_thread-mt \
        -lboost_filesystem \
        -lboost_program_options \
        -lboost_system

TARGET       = culturify-client

TEMPLATE     = app

SOURCES     += main.cpp\
               mainwindow.cpp \
               request.cpp \
               database.cpp

HEADERS     += mainwindow.h \
               request.h \
               config.h \
               database.h

FORMS       += mainwindow.ui
