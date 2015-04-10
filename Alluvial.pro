TEMPLATE = app

QT += qml quick widgets multimedia

SOURCES += main.cpp \
    mediaplayer.cpp \
    playlist_handler.cpp \
    playlist_item.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    settings_storage.h \
    mediaplayer.h \
    playlist_handler.h \
    playlist_item.h
DISTFILES += \
    qmldir.txt \
    Doxyfile
