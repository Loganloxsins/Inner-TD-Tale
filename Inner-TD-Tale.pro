QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Add the include directory to the INCLUDEPATH
INCLUDEPATH += $$PWD/include

# Update the paths to reflect the new directory structure
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/mainwindow.h

FORMS += \
    forms/mainwindow.ui

TRANSLATIONS += \
    translations/Inner-TD-Tale_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
