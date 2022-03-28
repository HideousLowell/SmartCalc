#include "credit_calc.h"
#include "errordialog.h"
#include "ui_credit_calc.h"

namespace s21 {
credit_calc::credit_calc(Controller *cntrl, QWidget *parent)
    : QDialog(parent), ui(new Ui::credit_calc), mycontrol(cntrl) {
    ui->setupUi(this);
}

credit_calc::~credit_calc() { delete ui; }

void credit_calc::on_calcButton_clicked() {
    bool ok1, ok2, ok3;
    double amount = ui->credit_amount_input->text().toDouble(&ok1);
    int term = ui->credit_term_input->text().toInt(&ok2);
    if (ui->comboBox->itemText(0) == "years") term *= 12;
    double rate = ui->inter_rate_input->text().toDouble(&ok3);
    ui->total_payment_label->clear();
    ui->overpayment_label->clear();
    ui->monthly_payment_label->clear();
    if (!(ok1 && ok2 && ok3 && amount > 0 && term > 0 && rate > 0)) {
        ErrorDialog someerror;
        someerror.setModal(true);
        someerror.exec();
    } else {
        std::vector<double> res;
        if (ui->annuity_radioButton->isChecked())
            res = mycontrol->annuity(amount, term, rate);
        else
            res = mycontrol->dif(amount, term, rate);
        ui->total_payment_label->setText(QString::number(res[0], 'c', 2));
        ui->overpayment_label->setText(QString::number(res[1], 'c', 2));
        ui->monthly_payment_label->setText(QString::number(res[2], 'c', 2));
        if (ui->diff_radioButton->isChecked())
            ui->monthly_payment_label->setText(ui->monthly_payment_label->text() + " ... " +
                                               QString::number(res[3], 'c', 2));
    }
}

}  //  namespace s21
