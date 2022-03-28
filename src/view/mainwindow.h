#pragma once

#include <QMainWindow>

#include "../controller/controller.h"
#include "../model/model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(Controller *cntrl, QWidget *parent = nullptr);
    ~MainWindow();

 private slots:
    void on_pushButton_C_clicked();
    void on_pushButton_AC_clicked();
    void buttons_clicked();
    void connect_buttons();
    void funcbuttons_clicked();
    void on_pushButton_start_clicked();

    void on_credit_calc_clicked();

 private:
    Ui::MainWindow *ui;
    Controller *mycontrol;
};

}  // namespace s21
