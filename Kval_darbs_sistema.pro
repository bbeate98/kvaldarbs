
QT       += core gui
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kval_darbs_sistema
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    pievienot.cpp \
    datubaze.cpp \
    skatit_pers.cpp \
    rediget.cpp \
    pievienot_sak.cpp \
    pievienot_ligums.cpp \
    pievienot_amatu.cpp \
    pievienot_kontaktinfo.cpp \
    pieivenot_adrese.cpp \
    dzest.cpp \
    pievienot_piekl.cpp

HEADERS  += mainwindow.h \
    pievienot.h \
    datubaze.h \
    skatit_pers.h \
    rediget.h \
    pievienot_sak.h \
    pievienot_ligums.h \
    pievienot_amatu.h \
    pievienot_kontaktinfo.h \
    pieivenot_adrese.h \
    dzest.h \
    pievienot_piekl.h

FORMS    += mainwindow.ui \
    pievienot.ui \
    skatit_pers.ui \
    rediget.ui \
    pievienot_sak.ui \
    pievienot_ligums.ui \
    pievienot_amatu.ui \
    pievienot_kontaktinfo.ui \
    pieivenot_adrese.ui \
    dzest.ui \
    pievienot_piekl.ui
LIBS += `pkg-config opencv --libs`


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
