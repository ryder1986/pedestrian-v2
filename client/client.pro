#-------------------------------------------------
#
# Project created by QtCreator 2017-09-04T14:35:50
#
#-------------------------------------------------

QT       += core gui
QT       +=network opengl
CONFIG +=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    videohandler.cpp

HEADERS  += mainwindow.h \
    client.h \
    common.h \
    protocol.h \
    yuvrender.h \
    config.h \
    videosrc.h \
    camera.h \
    videohandler.h

FORMS    += mainwindow.ui

LIBS +=   -lopencv_core  -lopencv_highgui  -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video
DEFINES+=CLIENT
