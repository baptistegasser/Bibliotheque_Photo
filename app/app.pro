QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../Bibliotheque_Photo.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db/dbmanager.cpp \
    db/filter.cpp \
    db/imagedao.cpp \
    db/imagedirdao.cpp \
    db/tagdao.cpp \
    imagefinder.cpp \
    main.cpp \
    mainwindow.cpp \
    modification_window.cpp \
    photocard.cpp \
    tagbutton.cpp

HEADERS += \
    db/dao.h \
    db/dbmanager.h \
    db/filter.h \
    db/imagedao.h \
    db/imagedirdao.h \
    db/tagdao.h \
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

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
