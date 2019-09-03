#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T14:51:14
#
#-------------------------------------------------

QT       += core gui sql dtkcore

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VoiceNotebook
TEMPLATE = app
PKGCONFIG += dtkwidget libavformat libavcodec libavutil
QT += multimedia


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
    src/views/rightview.cpp \
    src/views/leftview.cpp \
    src/views/folerwidgetitem.cpp \
    src/database/databaseoper.cpp \
    src/database/folderoper.cpp \
    src/Controllers/foldercontroller.cpp \
    src/views/leftfolderlist.cpp \
    src/views/textnoteitem.cpp \
    src/util/uiutil.cpp \
    src/views/rightnotelist.cpp \
    src/Controllers/notecontroller.cpp \
    src/database/noteoper.cpp \
    src/views/textnoteedit.cpp \
    src/views/mainpage.cpp \
    src/views/voicenoteitem.cpp \
    src/views/recordPage.cpp \
    src/views/recordingButton.cpp \
    src/views/waveform.cpp

HEADERS += \
    src/app \
    src/app/voicenotebookapp.h \
    src/views/mainwindow.h \
    src/views/dfmsplitter.h \
    src/views/rightview.h \
    src/views/leftview.h \
    src/views/folerwidgetitem.h \
    src/database/databaseoper.h \
    src/app/consts.h \
    src/database/folderoper.h \
    src/Controllers/foldercontroller.h \
    src/views/leftfolderlist.h \
    src/views/textnoteitem.h \
    src/util/uiutil.h \
    src/views/rightnotelist.h \
    src/Controllers/notecontroller.h \
    src/database/noteoper.h \
    src/views/textnoteedit.h \
    src/views/mainpage.h \
    src/views/voicenoteitem.h \
    src/views/recordPage.h \
    src/views/recordingButton.h \
    src/views/waveform.h

INCLUDEPATH += \
    src/app \
    src/views \
    src/database \
    src/Controllers \
    src/util


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
