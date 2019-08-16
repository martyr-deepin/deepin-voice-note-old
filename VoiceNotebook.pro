#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T14:51:14
#
#-------------------------------------------------

QT       += core gui sql dtkcore

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VoiceNotebook
TEMPLATE = app
PKGCONFIG += dtkwidget


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QMAKE_TARGET=\\\"$$TARGET\\\" QMAKE_VERSION=\\\"$$VERSION\\\"

isEmpty(QMAKE_ORGANIZATION_NAME) {
    DEFINES += QMAKE_ORGANIZATION_NAME=\\\"deepin\\\"
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 link_pkgconfig

SOURCES += \
    src/app/main.cpp \
    src/app/voicenotebookapp.cpp \
    src/views/mainwindow.cpp \
    src/views/dfmsplitter.cpp \
    src/views/leftfolderview.cpp \
    src/views/rightview.cpp \
    src/views/leftview.cpp \
    src/views/folerwidgetitem.cpp \
    src/database/databaseoper.cpp \
    src/database/folderoper.cpp \
    src/Controllers/foldercontroller.cpp

HEADERS += \
    src/app \
    src/app/voicenotebookapp.h \
    src/views/mainwindow.h \
    src/views/dfmsplitter.h \
    src/views/leftfolderview.h \
    src/views/rightview.h \
    src/views/leftview.h \
    src/views/folerwidgetitem.h \
    src/database/databaseoper.h \
    src/app/consts.h \
    src/database/folderoper.h \
    src/Controllers/foldercontroller.h

INCLUDEPATH += \
    src/app \
    src/views \
    src/database \
    src/Controllers


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
