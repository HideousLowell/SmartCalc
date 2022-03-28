#pragma once

#include <QDialog>

#include "../controller/controller.h"
#include "mainwindow.h"

namespace Ui {
class plot_dialog;
}

namespace s21 {
class plot_dialog : public QDialog {
    Q_OBJECT

 public:
    explicit plot_dialog(Controller *cntrl, QWidget *parent = nullptr);
    ~plot_dialog();

 private slots:
    void on_draw_plot_button_clicked();

 private:
    Ui::plot_dialog *ui;
    Controller *mycontrol;
};

}  //   namespace s21
