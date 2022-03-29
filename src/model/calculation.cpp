
#include <string>

#include "model.h"
#include "polish_notation.h"

namespace s21 {

static void use_operators(std::stack<double> *buf, char operation) {
    double n{buf->top()};
    buf->pop();
    double n1{buf->top()};
    buf->pop();
    if (operation == '+')
        buf->push(n1 + n);
    else if (operation == '-')
        buf->push(n1 - n);
    else if (operation == '/')
        buf->push(n1 / n);
    else if (operation == '*')
        buf->push(n1 * n);
    else if (operation == '^')
        buf->push(pow(n1, n));
    else if (operation == MOD)
        buf->push(fmod(n1, n));
}

static void use_functions(std::stack<double> *buf, char operation) {
    switch (operation) {
        case SIN:
            buf->top() = sin(buf->top());
            break;
        case SQRT:
            buf->top() = sqrt(buf->top());
            break;
        case COS:
            buf->top() = cos(buf->top());
            break;
        case TAN:
            buf->top() = tan(buf->top());
            break;
        case ATAN:
            buf->top() = atan(buf->top());
            break;
        case ACOS:
            buf->top() = acos(buf->top());
            break;
        case ASIN:
            buf->top() = asin(buf->top());
            break;
        case LN:
            buf->top() = log(buf->top());
            break;
        case LOG:
            buf->top() = log10(buf->top());
            break;
    }
}

void edit_line(std::string *data, char dot) {
    size_t n = data->length();
    while (n-- > 0) {
        if ((*data)[n] == '0') {
            data->erase(n, 1);
            continue;
        }
        if ((*data)[n] == dot)
            data->erase(n, 1);
        break;
    }
}

double final_calc_cycle(std::stack<std::pair<char, double> > output,
                        double x) {  // creating stack copy for graph
    std::stack<double> buf;
    while (!output.empty()) {
        if (output.top().first == 'x') {
            output.top().first = 0;
            output.top().second = x;
        }
        if (output.top().first == 0) {
            buf.push(output.top().second);
        } else {
            char tmp_char = output.top().first;
            if (priority(tmp_char) > 1)
                use_operators(&buf, tmp_char);
            else
                use_functions(&buf, tmp_char);
        }
        output.pop();
    }
    return buf.top();
}

void Model::calculate_to_string(double x) {
    double res = final_calc_cycle(output, x);
    data = std::to_string(res);
    if (data.find('.') != std::string::npos)
        edit_line(&data, '.');
    else if (data.find(',') != std::string::npos)
        edit_line(&data, ',');
}

void Model::calculate_for_plot(std::vector<double> *x, std::vector<double> *y, const double plot_size[]) {
    double x_pos = plot_size[0];
    double step = (plot_size[1] - plot_size[0]) * 1e-7;
    step = step < 0.01? 0.01: step;
    if (step < 0) step = -step;
    if (step == 0) step = 0.1;
    while (x_pos <= plot_size[1]) {
        x->push_back(x_pos);
        y->push_back(final_calc_cycle(output, x_pos));
        x_pos += step;
    }
}
}  // namespace s21
