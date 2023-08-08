QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    mainwindow.cpp \
    s21_calculator.c \
    s21_credit_calculator.c \
    s21_deposit_calculator.c \
    s21_is_correct.c \
    s21_stack.c \
    qcustomplot.cpp

HEADERS += \
    credit.h \
    deposit.h \
    mainwindow.h \
    s21_calculator.h \
    s21_credit_calculator.h \
    s21_deposit_calculator.h \
    s21_is_correct.h \
    s21_stack.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    deposit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
