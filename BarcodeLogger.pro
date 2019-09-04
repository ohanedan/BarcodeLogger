#-------------------------------------------------
#
# Project created by QtCreator 2019-08-29T15:48:31
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BarcodeLogger
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

VERSION_MAJOR = 1
VERSION_MINOR = 1
VERSION_PATCH = 2

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_PATCH=$$VERSION_PATCH" \
       GIT_CURRENT="\\\"$(shell git -C \""$$_PRO_FILE_PWD_"\" describe --always)\\\""


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17 object_parallel_to_source

SOURCES += \
        controller.cpp \
        database.cpp \
        dialog/dialog_about.cpp \
        dialog/dialog_barcodelist.cpp \
        dialog/dialog_settings.cpp \
        isaver.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        barcode.hpp \
        controller.h \
        database.h \
        dialog/dialog_about.h \
        dialog/dialog_barcodelist.h \
        dialog/dialog_settings.h \
        isaver.h \
        mainwindow.h \
        settings.hpp

FORMS += \
  MainWindow.ui \
  dialog/dialog_about.ui \
  dialog/dialog_barcodelist.ui \
  dialog/dialog_settings.ui

TRANSLATIONS += \
  languages/tr.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  resources/resources.qrc

RC_ICONS += resources/barcode.ico
