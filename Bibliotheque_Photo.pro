QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db/dbmanager.cpp \
    db/filter.cpp \
    imagefinder.cpp \
    main.cpp \
    mainwindow.cpp \
    model/image.cpp \
    model/imagedir.cpp \
    model/tag.cpp \
    modification_window.cpp \
    photocard.cpp \
    tagbutton.cpp

HEADERS += \
    db/dbmanager.h \
    db/filter.h \
    imagefinder.h \
    mainwindow.h \
    model/image.h \
    model/imagedir.h \
    model/tag.h \
    modification_window.h \
    photocard.h \
    tagbutton.h

FORMS += \
    mainwindow.ui \
    modification_window.ui \
    photocard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
