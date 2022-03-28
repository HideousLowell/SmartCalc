#include "mainwindow.h"
#include "../model/model.h"
#include "../controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    s21::Model mymodel;
    s21::Controller mycontrol(&mymodel);
    QApplication a(argc, argv);
    s21::MainWindow w(&mycontrol);
    w.show();
    return a.exec();
}
