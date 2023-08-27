#include(Model/include.pri)
#include(View/include.pri)
#include(Controller/include.pri)

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/Controller.cpp \
    Model/Model.cpp \
    View/consoleView.cpp \
    View/credit.cpp \
    View/deposit.cpp \
    View/mainwindow.cpp \
    View/qcustomplot.cpp \
    main.cpp \
    s21_credit_calculator.c \
    s21_deposit_calculator.c \

HEADERS += \
    Controller/Controller.h \
    Model/Arithmetic.h \
    Model/Model.h \
    View/View.h \
    View/consoleView.h \
    View/credit.h \
    View/deposit.h \
    View/mainwindow.h \
    View/qcustomplot.h \
    s21_credit_calculator.h \
    s21_deposit_calculator.h \

FORMS += \
    View/credit.ui \
    View/deposit.ui \
    View/mainwindow.ui \
#    credit.ui \
#    deposit.ui \
#    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Controller/include.pri \
    Model/include.pri \
    View/include.pri
