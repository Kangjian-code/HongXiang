#-------------------------------------------------
#
# Project created by QtCreator 2019-01-03T20:01:03
#
#-------------------------------------------------

QT       += core gui charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS   +=    -std=c++11

TARGET = hx_client
TEMPLATE = app


SOURCES += main.cpp
include(Interface/Interface.pri)
include(Data/Data.pri)
include(3D/3D.pri)

RESOURCES += \
	img.qrc \
	qss.qrc \
