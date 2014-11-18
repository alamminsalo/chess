TEMPLATE = app

QT += qml quick widgets sql

SOURCES += main.cpp \
    startexternal.cpp \
    dbconnector.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    startexternal.h \
    dbconnector.h

CONFIG += console

OTHER_FILES +=
