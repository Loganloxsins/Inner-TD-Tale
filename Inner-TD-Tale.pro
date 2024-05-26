QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Add the include directory to the INCLUDEPATH，不然头文件包含都得写成#include "include/map/grid.h"
INCLUDEPATH += $$PWD/include

# Correctly collect all .cpp files in the 'src' directory
file_cpp = $$files($$PWD/src/*.cpp,true)
win32:file_cpp ~= s|\\\\|/|g
for(file, file_cpp):SOURCES += $$file

# Collect all .h files in the 'include' directory assuming that's where they are
file_h = $$files($$PWD/include/*.h,true)
win32:file_h ~= s|\\\\|/|g
for(file, file_h):HEADERS += $$file




file_ui = $$files($$PWD/forms/*.ui, true)
win32:file_ui ~= s|\\\\|/|g
for(file, file_ui):FORMS += $$file

TRANSLATIONS += \
    translations/Inner-TD-Tale_zh_CN.ts


CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



