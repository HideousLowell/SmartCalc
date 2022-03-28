#pragma once

#include <QDialog>
#include <QVector>

#include "../controller/controller.h"

namespace Ui {
class CalcPlot;
}

namespace s21 {

class CalcPlot : public QDialog {
    Q_OBJECT

 public:
    explicit CalcPlot(Controller *cntrl, double plot_size[], bool dots);
    ~CalcPlot();

 private:
    Ui::CalcPlot *ui;
    Controller *mycontrol;
    void drawing(double plot_size[], bool dots);
};

}  // namespace s21
