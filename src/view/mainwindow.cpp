#include "mainwindow.h"

#include "calcplot.h"
#include "credit_calc.h"
#include "errordialog.h"
#include "plot_dialog.h"
#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(Controller *cntrl, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), mycontrol(cntrl) {
    ui->setupUi(this);
    connect_buttons();
}

void MainWindow::connect_buttons() {
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(funcbuttons_clicked()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(buttons_clicked()));
}

void MainWindow::buttons_clicked() {
    if (ui->main_input->text() == "0") ui->main_input->clear();
    QPushButton *button = (QPushButton *)sender();
    ui->main_input->setText(ui->main_input->text() + button->text());
}

void MainWindow::funcbuttons_clicked() {
    if (ui->main_input->text() == "0") ui->main_input->clear();
    QPushButton *button = (QPushButton *)sender();
    ui->main_input->setText(ui->main_input->text() + button->text() + "(");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_C_clicked() { ui->main_input->backspace(); }

void MainWindow::on_pushButton_AC_clicked() { ui->main_input->clear(); }

void MainWindow::on_pushButton_start_clicked() {
    double x = 0;
    std::string my = ui->main_input->text().toStdString();
    bool error = mycontrol->set_validate_data(my);
    if (error) {
        ErrorDialog someerror;
        someerror.setModal(true);
        someerror.exec();
    } else if (ui->main_input->text().contains('x')) {
        if (ui->x_input->text().length() == 0) {
            plot_dialog mydialog(mycontrol);
            mydialog.setModal(true);
            mydialog.exec();
            return;
        } else {
            bool ok = false;
            x = ui->x_input->text().toDouble(&ok);
            if (ok) {
                ui->main_input->setText(QString::fromStdString(mycontrol->calc(x)));
            } else {
                ErrorDialog someerror;
                someerror.setModal(true);
                someerror.exec();
            }
        }
    } else {
        ui->main_input->setText(QString::fromStdString(mycontrol->calc(x)));
    }
}

void MainWindow::on_credit_calc_clicked() {
    credit_calc mycreditcalc(mycontrol);
    mycreditcalc.setModal(true);
    mycreditcalc.exec();
}

}  // namespace s21
