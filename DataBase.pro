QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lpqxx

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
    all_tables.cpp \
    check_connect.cpp \
    columnadd.cpp \
    connect_db.cpp \
    connect_table.cpp \
    create_db.cpp \
    findcondition.cpp \
    func.cpp \
    main.cpp \
    mainwindow.cpp \
    table.cpp

HEADERS += \
    all_tables.h \
    check_connect.h \
    columnadd.h \
    connect_db.h \
    connect_table.h \
    create_db.h \
    findcondition.h \
    func.h \
    mainwindow.h \
    table.h

FORMS += \
    all_tables.ui \
    check_connect.ui \
    columnadd.ui \
    connect_db.ui \
    connect_table.ui \
    create_db.ui \
    findcondition.ui \
    func.ui \
    mainwindow.ui \
    table.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
