TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        audio.cpp \
        button.cpp \
        camera.cpp \
        earphone.cpp \
        image.cpp \
        main.cpp \
        process.cpp \
        record.cpp \
        scope.cpp \
        text.cpp

target.path = /etc/Scope
INSTALLS += target

HEADERS += \
    audio.h \
    button.h \
    camera.h \
    earphone.h \
    image.h \
    main.h \
    process.h \
    record.h \
    scope.h \
    text.h

QMAKE_CXXFLAGS += -std=c++0x -pthread -lasound
LIBS += -pthread -lrt -lpthread -lbcm2835

CONFIG += link_pkgconfig
PKGCONFIG += opencv
