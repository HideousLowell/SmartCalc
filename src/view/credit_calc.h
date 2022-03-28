#pragma once

#include <QDialog>

#include "../controller/controller.h"

namespace Ui {
class credit_calc;
}

namespace s21 {
class credit_calc : public QDialog {
    Q_OBJECT

 public:
    explicit credit_calc(Controller *cntrl, QWidget *parent = nullptr);
    ~credit_calc();

 private slots:
    void on_calcButton_clicked();

 private:
    Ui::credit_calc *ui;
    Controller *mycontrol;
};

}  // namespace s21
