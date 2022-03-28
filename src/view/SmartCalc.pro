QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cpp \
    ../model/credit_model.cpp \
    calcplot.cpp \
    ../model/calculation.cpp \
    ../model/polish_notation.cpp \
    ../model/validation.cpp \
    credit_calc.cpp \
    errordialog.cpp \
    main.cpp \
    mainwindow.cpp \
    plot_dialog.cpp \
    qcustomplot.cpp

HEADERS += \
    ../model/credit_model.h \
    calcplot.h \
    ../controller/controller.h \
    ../model/model.h \
    ../model/polish_notation.h \
    credit_calc.h \
    errordialog.h \
    mainwindow.h \
    plot_dialog.h \
    qcustomplot.h

FORMS += \
    calcplot.ui \
    credit_calc.ui \
    errordialog.ui \
    mainwindow.ui \
    plot_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
