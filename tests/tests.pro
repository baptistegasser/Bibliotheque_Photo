QT += testlib sql widgets

include(../Bibliotheque_Photo.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_dbmanager.cpp

#----------------------------------------------
# Include the header and sources of the app
#----------------------------------------------
APP = ../app

INCLUDEPATH += $$APP/

SOURCES += \
    $$APP/db/dbmanager.cpp \
    $$APP/db/filter.cpp \
    $$APP/db/imagedao.cpp \
    $$APP/db/imagedirdao.cpp \
    $$APP/db/tagdao.cpp

RESOURCES += \
    $$APP/resources.qrc
