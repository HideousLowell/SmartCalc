#include "polish_notation.h"
#include "model.h"

namespace s21 {
static int left_associative(char c);

static void polish_notation_s(const std::string &data, std::stack<char> *operators, size_t *n) {
    if (data.find("sin", *n) == *n) {
        operators->push(SIN);
        *n += 2;
    } else if (data.find("sqrt", *n) == *n) {
        operators->push(SQRT);
        *n += 3;
    }
}

static void polish_notation_l(const std::string &data, std::stack<char> *operators, size_t *n) {
    if (data.find("ln", *n) == *n) {
        operators->push(LN);
        *n += 1;
    } else if (data.find("log", *n) == *n) {
        operators->push(LOG);
        *n += 2;
    }
}

static void polish_notation_a(const std::string &data, std::stack<char> *operators, size_t *n) {
    if (data.find("acos", *n) == *n)
        operators->push(ACOS);
    else if (data.find("asin", *n) == *n)
        operators->push(ASIN);
    else if (data.find("atan", *n) == *n)
        operators->push(ATAN);
    *n += 3;
}

static void polish_notation_shift(std::stack<std::pair<char, double> > *output,
                                  std::stack<char> *operators) {
    while (!operators->empty()) {
        if (operators->top() != '(') output->push({operators->top(), 0});
        operators->pop();
    }
}

static void polish_notation_priority(const char data_oper, std::stack<std::pair<char, double> > *output,
                                     std::stack<char> *operators) {
    if (!operators->empty()) {
        int pr_data = priority(data_oper);
        int pr_oper = priority(operators->top());
        while (pr_oper > pr_data || (pr_data == pr_oper && left_associative(pr_oper))) {
            char tmp = operators->top();
            operators->pop();
            output->push({tmp, 0});
            if (operators->empty()) break;
            pr_oper = priority(operators->top());
        }
    }
    operators->push(data_oper);
}

static void polish_notation_brackets(std::stack<std::pair<char, double> > *output,
                                     std::stack<char> *operators, int *br) {
    while (*br > 0) {
        char c = operators->top();
        operators->pop();
        if (c == '(')
            (*br)--;
        else
            output->push({c, 0});
    }
    if (!operators->empty() && is_function(operators->top())) {
        output->push({operators->top(), 0});
        operators->pop();
    }
}

int priority(char c) {
    int flag = 0;
    if (c == '(' || is_function(c))
        flag = 1;
    else if (c == '+' || c == '-')
        flag = 2;
    else if (c == '*' || c == '/' || c == MOD)
        flag = 3;
    else if (c == '^')
        flag = 4;
    return flag;
}

static int left_associative(char c) { return (c == 2 || c == 3); }

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_function(char c) { return (c >= COS && c <= ATAN); }

static bool is_unar(int n, const std::string &data) {
    bool res = true;
    while (--n >= 0) {
        if (data[n] == ' ') continue;
        if ((data[n] != 0 && is_digit(data[n])) || data[n] == ')') res = false;
        break;
    }
    return res;
}

void s21::Model::polish_notation() {
    while (!output.empty())
        output.pop();
    std::stack<std::pair<char, double> > reversed;
    std::stack<char> operators;
    int sign = 1;
    int br = 0;
    for (std::size_t n = 0; n < data.length(); n++) {
        if (is_digit(data[n])) {
            std::size_t sz = 0;
            double value = std::stod(data.substr(n), &sz) * sign;
            if (sign == -1) sign = -sign;
            n += sz - 1;
            reversed.push({0, value});
        } else if (data[n] == 'x') {
            reversed.push({data[n], 0});
        } else if (data[n] == 'c' && data.find("cos(", n) == n) {
            operators.push(COS);
            n += 2;
        } else if (data[n] == 's') {
            polish_notation_s(data, &operators, &n);
        } else if (data[n] == 't' && data.find("tan(", n) == n) {
            operators.push(TAN);
            n += 2;
        } else if (data[n] == 'l') {
            polish_notation_l(data, &operators, &n);
        } else if (data[n] == 'a') {
            polish_notation_a(data, &operators, &n);
        } else if (data[n] == 'm' && data.find("mod", n) == n) {
            operators.push(MOD);
            data += 2;
        } else if (data[n] == '(') {
            operators.push(data[n]);
            br++;
        } else if (priority(data[n]) == 2 && is_unar(n, data)) {
            if (data[n] == '-') sign = -1;
        } else if (priority(data[n]) > 1) {
            polish_notation_priority(data[n], &reversed, &operators);
        } else if (data[n] == ')') {
            polish_notation_brackets(&reversed, &operators, &br);
        }
    }
    polish_notation_shift(&reversed, &operators);
    while (!reversed.empty()) {
        output.push(reversed.top());
        reversed.pop();
    }
    }
}   // namespace s21
