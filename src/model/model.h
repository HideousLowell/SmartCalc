#pragma once

#include <math.h>

#include <stack>
#include <string>
#include <vector>

namespace s21 {

enum Choise {
    MOD = 10,
    COS = 11,
    SIN = 12,
    TAN = 13,
    ACOS = 14,
    ASIN = 15,
    SQRT = 16,
    LN = 17,
    LOG = 18,
    ATAN = 19,
};

class Model {
 private:
    std::stack<std::pair<char, double> > output;
    std::string data;

 public:
    Model() {}
    explicit Model(const std::string &other) : data(other) {}
    void set_data(const std::string &other) { data = other; }
    std::string &get_data() { return data; }
    bool validation();
    void polish_notation();
    void calculate_to_string(double x = 0);
    void calculate_for_plot(std::vector<double> *x, std::vector<double> *y, const double plot_size[]);
    ~Model(){}
};

}  // namespace s21
