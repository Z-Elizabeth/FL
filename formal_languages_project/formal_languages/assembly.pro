QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appearance.cpp \
    arrow.cpp \
    circle.cpp \
    main.cpp \
    mainwindow.cpp \
    sqribblearea.cpp \
    tex.cpp \
    text.cpp

HEADERS += \
    appearance.h \
    arrow.h \
    circle.h \
    mainwindow.h \
    scribblearea.h \
    tex.h \
    text.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
