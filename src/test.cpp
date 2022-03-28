#include <gtest/gtest.h>
#include "model/model.h"
#include "controller/controller.h"
#include "model/credit_model.h"


TEST(s21_ariphmetic_test, 1) {
    s21::Model mymodel("5.12 / 5 + 5.2 * 5 - -5.5");
    std::string realres("32.524");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_sincos_test, 1) {
    s21::Model mymodel("sin(5) + cos(3)");
    std::string realres("-1.948917");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_tanatan_test, 1) {
    s21::Model mymodel("tan(5) - atan(3)");
    std::string realres("-4.629561");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_acos_test, 1) {
    s21::Model mymodel("acos(3)");
    std::string realres("nan");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_asin_test, 1) {
    s21::Model mymodel("asin(1/2)");
    std::string realres("0.523599");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_lnlog_test, 1) {
    s21::Model mymodel("ln(2) * log(3)");
    std::string realres("0.330715");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_sqrtpow_test, 1) {
    s21::Model mymodel("sqrt(81) + 3 ^ 3");
    std::string realres("36");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_mod_test, 1) {
    s21::Model mymodel("101.66 mod 10");
    std::string realres("1.66");
    mymodel.polish_notation();
    mymodel.calculate_to_string();
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(s21_add_test, 2) {
    s21::Model mymodel("50 + 50 + 30");
    std::string realres("130");
    mymodel.polish_notation();
    mymodel.calculate_to_string(5);
    std::string res = mymodel.get_data();
    ASSERT_EQ(realres, res);
}

TEST(credit_test, annuity) {
    s21::CreditModel mymodel;
    std::vector<double> res = mymodel.annuity_payment(1000, 12, 12);
    std::vector<double> realres{1066.20, 66.20, 88.85};
    for (int i = 0; i < 3; i++)
        ASSERT_NEAR(res[i], realres[i], 0.1);
}

TEST(credit_test, dif) {
    s21::CreditModel mymodel;
    std::vector<double> res = mymodel.dif_payment(10000, 6, 6);
    std::vector<double> realres{10175.00, 175.00, 1716.67, 1675.00};
    for (int i = 0; i < 4; i++)
        ASSERT_NEAR(res[i], realres[i], 0.1);
}

TEST(graph_test, 1) {
    s21::Model mymodel("x * x");
    mymodel.polish_notation();
    std::vector<double> x, y;
    double plot_size[]{-10, 10, -10, 10};
    mymodel.calculate_for_plot(&x, &y, plot_size);
    ASSERT_EQ(x[0], -10);
    ASSERT_EQ(y[0], 100);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
