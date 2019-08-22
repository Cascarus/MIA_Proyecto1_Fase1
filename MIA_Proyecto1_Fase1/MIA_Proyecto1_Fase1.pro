QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
        main.cpp \
    parser.cpp \
    scanner.cpp \
    nodo_mbr.cpp \
    Nodo_Particion.cpp \
    Nodo_EBR.cpp \
    Nodo_AST.cpp \
    Graficar.cpp \
    Interprete.cpp \
    abstracta.cpp \
    MKDISK.cpp \
    RMDISK.cpp \
    FDISK.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    parser.output

HEADERS += \
    parser.h \
    scanner.h \
    Nodo_MBR.h \
    Nodo_Particion.h \
    Nodo_EBR.h \
    Nodo_AST.h \
    Graficar.h \
    Interprete.h \
    abstracta.h \
    MKDISK.h \
    RMDISK.h \
    FDISK.h
