#pragma once

#include <QDialog>

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog {
    Q_OBJECT

 public:
    explicit ErrorDialog(QWidget *parent = nullptr);
    ~ErrorDialog();

 private:
    Ui::ErrorDialog *ui;
};
