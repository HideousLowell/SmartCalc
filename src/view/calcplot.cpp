#include <vector>
#include <list>
#include <QVector>

#include "calcplot.h"
#include "ui_calcplot.h"

namespace s21 {

CalcPlot::CalcPlot(Controller *cntrl, double plot_size[], bool dots)
    : QDialog(nullptr), ui(new Ui::CalcPlot), mycontrol(cntrl) {
    ui->setupUi(this);
    drawing(plot_size, dots);
}

void CalcPlot::drawing(double plot_size[], bool dots) {
    ui->widget->xAxis->setRange(plot_size[0], plot_size[1]);
    ui->widget->yAxis->setRange(plot_size[2], plot_size[3]);
    std::vector<double> std_x, std_y;
    mycontrol->calc_plot(&std_x, &std_y, plot_size);
    QVector<double> qt_x  = QVector<double>(std_x.begin(), std_x.end());
    QVector<double> qt_y  = QVector<double>(std_y.begin(), std_y.end());
    ui->widget->addGraph();
    QPen Pen1;
    Pen1.setColor(QColor(Qt::red));
    if (dots) {
        ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 3));
    } else {
        Pen1.setWidthF(3);
    }
    ui->widget->graph(0)->setPen(Pen1);
    ui->widget->graph(0)->addData(qt_x, qt_y);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

CalcPlot::~CalcPlot() { delete ui; }

}  // namespace s21
