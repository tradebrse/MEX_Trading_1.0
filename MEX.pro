#-------------------------------------------------
#
# Project created by QtCreator 2015-09-08T10:21:59
#
#-------------------------------------------------

QT       += core gui

#########################
### load SQL Package  ###
#########################

QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEX
TEMPLATE = app


SOURCES += main.cpp\
        mex_login.cpp \
    mex_main.cpp \
    mex_userpanel.cpp \
    mex_myaccount.cpp \
    mex_trader.cpp \
    mex_product.cpp \
    mex_order.cpp \
    mex_tradelog.cpp

HEADERS  += mex_login.h \
    mex_main.h \
    mex_userpanel.h \
    mex_myaccount.h \
    mex_trader.h \
    mex_product.h \
    mex_order.h \
    mex_tradelog.h

FORMS    += mex_login.ui \
    mex_main.ui \
    mex_userpanel.ui \
    mex_myaccount.ui \
    mex_tradelog.ui
