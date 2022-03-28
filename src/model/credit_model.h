#pragma once

#include <math.h>

#include <vector>

namespace s21 {

class CreditModel {
 public:
    std::vector<double> annuity_payment(double amount, int term, double rate);
    std::vector<double> dif_payment(double amount, int term, double rate);
};

}  // namespace s21
