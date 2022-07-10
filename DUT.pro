QT  += sql
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auteurf.cpp \
    main.cpp \
    mainwindow.cpp \
    modele/BD.cpp \
    traitement/Auteur.cpp \
    traitement/backend_interface_headers(0.1.0).cpp

HEADERS += \
    auteurf.h \
    mainwindow.h \
    modele/BD.h \
    traitement/Auteur.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    modele/db_v0.0.1.sql \
    modele/dut_puc2442_proj.db \
    uml/uml_class_diag.edg \
    uml/uml_use_case_diag.edg
