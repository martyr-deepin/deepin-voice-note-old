#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T14:51:14
#
#-------------------------------------------------

QT       += core gui sql dtkcore

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets dbus

TARGET = deepin-voice-note
TEMPLATE = app
PKGCONFIG += dtkwidget
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
    src/views/waveform.cpp \
    src/views/playingbutton.cpp \
    src/views/sliderhandler.cpp \
    src/views/mysliderbar.cpp \
    src/views/myslider.cpp \
    src/views/fileexistsdialog.cpp \
    src/views/addtextbtn.cpp \
    src/views/folderimage.cpp \
    src/views/renameedit.cpp \
    src/views/sliderhandle.cpp \
    src/views/intancer.cpp \
    src/views/menubutton.cpp \
    src/views/addfolderbutton.cpp \
    src/views/waveformreplay.cpp \
    src/views/replaysliderbar.cpp \
    src/views/initemptypage.cpp \
    src/views/theadmngintancer.cpp \
    src/Controllers/notewatchercontroller.cpp

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
    src/views/waveform.h \
    src/views/playingbutton.h \
    src/views/sliderhandler.h \
    src/views/mysliderbar.h \
    src/views/myslider.h \
    src/views/fileexistsdialog.h \
    src/views/addtextbtn.h \
    src/views/folderimage.h \
    src/views/renameedit.h \
    src/views/sliderhandle.h \
    src/views/intancer.h \
    src/views/menubutton.h \
    src/views/addfolderbutton.h \
    src/views/waveformreplay.h \
    src/views/replaysliderbar.h \
    src/views/initemptypage.h \
    src/views/theadmngintancer.h \
    src/Controllers/notewatchercontroller.h

INCLUDEPATH += \
    src/app \
    src/views \
    src/database \
    src/Controllers \
    src/util


FORMS +=

# Default rules for deployment.
isEmpty(BINDIR):BINDIR=/usr/bin
isEmpty(APPDIR):APPDIR=/usr/share/applications
isEmpty(DSRDIR):DSRDIR=/usr/share/deepin-voice-note

target.path = $$INSTROOT$$BINDIR

desktop.path = $$INSTROOT$$APPDIR
desktop.files =  deepin-voice-note.desktop

icon_files.path = /usr/share/icons/hicolor/scalable/apps
icon_files.files = $$PWD/image/deepin-voice-note.svg

INSTALLS += target desktop icon_files

RESOURCES += \
    images.qrc

