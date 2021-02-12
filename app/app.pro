QT       += core gui sql concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../Bibliotheque_Photo.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db/albumdao.cpp \
    db/db.cpp \
    db/directorydao.cpp \
    db/imagedao.cpp \
    db/imagesearch.cpp \
    db/tagdao.cpp \
    dialogcreatetag.cpp \
    directorymanager.cpp \
    dirindexer.cpp \
    filtermenu.cpp \
    flowlayout.cpp \
    main.cpp \
    mainwindow.cpp \
    model/directory.cpp \
    model/image.cpp \
    model/tag.cpp \
    modification_window.cpp \
    photocard.cpp \
    qinputcustom.cpp \
    resizable_rubber_rand.cpp \
    tagbutton.cpp

HEADERS += \
    db/albumdao.h \
    db/dao.h \
    db/db.h \
    db/directorydao.h \
    db/imagedao.h \
    db/imagesearch.h \
    db/tagdao.h \
    dialogcreatetag.h \
    directorymanager.h \
    dirindexer.h \
    filtermenu.h \
    mainwindow.h \
    model/directory.h \
    model/image.h \
    model/tag.h \
    modification_window.h \
    photocard.h \
    qinputcustom.h \
    resizable_rubber_rand.h \
    tagbutton.h

FORMS += \
    dialogcreatetag.ui \
    directorymanager.ui \
    filtermenu.ui \
    mainwindow.ui \
    modification_window.ui \
    photocard.ui

RESOURCES += \
    resources.qrc

# For MacOS BigSur, when running qmake to silence warning about SDK version
CONFIG += \
    sdk_no_version_check

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
