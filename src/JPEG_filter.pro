#-------------------------------------------------
#
# Project created by QtCreator 2013-05-08T16:20:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JPEG_filter
TEMPLATE = app


SOURCES += main.cpp\
           jpegfilter.cpp \
    settingsdialog.cpp \
    gaussianblur.cpp \
    progressbar.cpp

HEADERS  += \
    settingsdialog.h \
    gaussianblur.h \
    jpegfilter.h \
    progressbar.h

FORMS    += jpegfilter.ui \
    settingsdialog.ui \
    progressbar.ui

RESOURCES += \
    res/res.qrc
