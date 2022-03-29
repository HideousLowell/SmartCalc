#include "controller.h"

namespace s21 {

bool Controller::set_validate_data(const std::string &input) {
    main_model->set_data(input);
    return main_model->validation();
}

std::string &Controller::calc(double x) {
    main_model->polish_notation();
    main_model->calculate_to_string(x);
    return main_model->get_data();
}

void Controller::calc_plot(std::vector<double> *x, std::vector<double> *y, double plot_size[]) {
    main_model->polish_notation();
    return main_model->calculate_for_plot(x, y, plot_size);
}

std::vector<double> Controller::annuity(double amount, int term, double rate) {
    return credit_model->annuity_payment(amount, term, rate);
}

std::vector<double> Controller::dif(double amount, int term, double rate) {
    return credit_model->dif_payment(amount, term, rate);
}

}  // namespace s21
