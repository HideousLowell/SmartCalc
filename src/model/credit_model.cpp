#include "credit_model.h"

namespace s21 {

std::vector<double> CreditModel::annuity_payment(double amount, int term, double rate) {
    rate /= (100 * 12);
    double monthly_payment = amount * (rate / (1 - pow(1 + rate, -term)));
    double amount_to_return = monthly_payment * term;
    double overpayment = amount_to_return - amount;
    std::vector<double> res{amount_to_return, overpayment,  monthly_payment};
    return res;
}

std::vector<double> CreditModel::dif_payment(double amount, int term, double rate) {
    rate /= (100 * 12);
    double monthly_percent = amount * rate;
    double monthly_payment = amount / term + monthly_percent;
    double last_month_payment{monthly_payment};
    double amount_to_return{monthly_payment};
    double loan_balance{amount};
    for (int i = term; i > 1; i--) {
        loan_balance = loan_balance - last_month_payment + monthly_percent;
        monthly_percent = loan_balance * rate;
        last_month_payment = amount / term + loan_balance * rate;
        amount_to_return += last_month_payment;
    }
    double overpayment = amount_to_return - amount;
    std::vector<double> res{amount_to_return, overpayment,  monthly_payment, last_month_payment};
    return res;
}

}  // namespace s21
