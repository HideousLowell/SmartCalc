#pragma once
#include <string>
#include <vector>

#include "../model/credit_model.h"
#include "../model/model.h"

namespace SmartCalc {

class Controller {
 private:
    Model *main_model;
    CreditModel *credit_model;

 public:
    explicit Controller(Model *m) : main_model(m) {}
    bool set_validate_data(const std::string &input);
    std::string &get_data();
    std::string &calc(double x);
    void calc_plot(std::vector<double> *x, std::vector<double> *y, double plot_size[]);
    std::vector<double> annuity(double amount, int term, double rate);
    std::vector<double> dif(double amount, int term, double rate);
};

}  // namespace SmartCalc
