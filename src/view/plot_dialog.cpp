#include "plot_dialog.h"

#include "calcplot.h"
#include "ui_plot_dialog.h"
#include "errordialog.h"

namespace s21 {
plot_dialog::plot_dialog(Controller *cntrl, QWidget *parent)
    : QDialog(parent), ui(new Ui::plot_dialog), mycontrol(cntrl) {
    ui->setupUi(this);
}

plot_dialog::~plot_dialog() { delete ui; }

void plot_dialog::on_draw_plot_button_clicked() {
    bool ok1, ok2, ok3, ok4;
    double plot_size[4];
    plot_size[0] = ui->min_x_input->text().toDouble(&ok1);
    plot_size[1] = ui->max_x_input->text().toDouble(&ok2);
    plot_size[2] = ui->min_y_input->text().toDouble(&ok3);
    plot_size[3] = ui->max_y_input->text().toDouble(&ok4);
    if (!(ok1 && ok2 && ok3 && ok4)) {
        ErrorDialog someerror;
        someerror.setModal(true);
        someerror.exec();
    } else {
        CalcPlot myplot(mycontrol, plot_size, ui->dots_radio_button->isChecked());
        myplot.setModal(true);
        myplot.exec();
    }
}

}  //   namespace s21
