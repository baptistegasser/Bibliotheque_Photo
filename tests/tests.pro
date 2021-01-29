QT += testlib
QT -= gui

include(../Bibliotheque_Photo.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test.cpp
