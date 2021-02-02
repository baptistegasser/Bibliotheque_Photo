QT += testlib sql widgets

include(../Bibliotheque_Photo.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    dbtest.h \
    tst_dbmanager.h \
    tst_directorydao.h \
    tst_imagedao.h \
    tst_tagdao.h

SOURCES += \
    main.cpp \
    tst_dbmanager.cpp \
    tst_directorydao.cpp \
    tst_imagedao.cpp \
    tst_tagdao.cpp

#----------------------------------------------
# Include the header and sources of the app
#----------------------------------------------
APP = ../app

INCLUDEPATH += $$APP/

SOURCES += \
    $$APP/db/dbmanager.cpp \
    $$APP/db/filter.cpp \
    $$APP/db/imagedao.cpp \
    $$APP/db/tagdao.cpp \
    $$APP/db/directorydao.cpp \
    $$APP/model/directory.cpp

RESOURCES += \
    $$APP/resources.qrc
