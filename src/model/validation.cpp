#include <cstring>
#include <string>
#include <iostream>

#include "polish_notation.h"
#include "model.h"

namespace s21 {

static bool allowable_char(const char c);
static void validation_errors(const std::string &data, const size_t &n, bool *parse_error, bool *empty);
static bool validation_br(const std::string &data);
static void validation_s(const std::string &data, size_t *n, bool *parse_error);
static void validation_c(const std::string &data, size_t *n, bool *parse_error);
static void validation_a(const std::string &data, size_t *n, bool *parse_error);
static void validation_tan(const std::string &data, size_t *n, bool *parse_error);
static void validation_l(const std::string &data, size_t *n, bool *parse_error);
static void validation_m(const std::string &data, size_t *n, bool *parse_error);

bool s21::Model::validation() {
    if (validation_br(data)) return true;
    size_t n = 0;
    bool parse_error = false;
    bool empty = true;
    while (n < data.length() && !parse_error) {
        if (allowable_char(data[n]))
            validation_errors(data, n, &parse_error, &empty);
        else if (data[n] == 's')
            validation_s(data, &n, &parse_error);
        else if (data[n] == 'c')
            validation_c(data, &n, &parse_error);
        else if (data[n] == 'a')
            validation_a(data, &n, &parse_error);
        else if (data[n] == 't')
            validation_tan(data, &n, &parse_error);
        else if (data[n] == 'l')
            validation_l(data, &n, &parse_error);
        else if (data[n] == 'm')
            validation_m(data, &n, &parse_error);
        else
            parse_error = true;
        n++;
    }
    return parse_error || empty;
}

static bool allowable_char(const char c) {
    bool result = false;
    if ((c >= '0' && c <= '9') || c == 'e')
        result = true;
    else if (c != MOD && priority(c) > 1)
        result = true;
    else if (c == '(' || c == ')' || c == 'x' || c == ',' || c == '.' || c == ' ')
        result = true;
    return result;
}

static void validation_errors(const std::string &data, const size_t &n, bool *parse_error, bool *empty) {
    if (*empty == true && data[n] != ' ') *empty = false;
    if (priority(data[n]) > 1) {
        if (n == data.length() - 1) *parse_error = true;
        else if (priority(data[n + 1]) > 2) *parse_error = true;
    }
    if (data[n] == 'x') {
        if (n != data.length() - 1 && is_digit(data[n + 1]))
            *parse_error = true;
        if (n != 0 && is_digit(data[n - 1]))
            *parse_error = true;
    }
    if (data[n] == '(' && data[n + 1] == ')') *parse_error = true;
    if (data[n] == ')' && data[n + 1] == '(') *parse_error = true;
}

static bool validation_br(const std::string &data) {
    int br = 0;
    for (size_t i = 0; i < data.length(); i++) {
        if (data[i] == '(')
            br++;
        else if (data[i] == ')')
            br--;
    }
    return (bool)br;
}

static void validation_s(const std::string &data, size_t *n, bool *parse_error) {
    if (data.find("sin(", *n) == *n)
        *n += 3;
    else if (data.find("sqrt(", *n) == *n)
        *n += 4;
    else
        *parse_error = true;
}

static void validation_c(const std::string &data, size_t *n, bool *parse_error) {
    if (data.find("cos(", *n) == *n)
        *n += 3;
    else
        *parse_error = true;
}

static void validation_a(const std::string &data, size_t *n, bool *parse_error) {
    if (data.find("acos(", *n) == *n)
        *n += 4;
    else if (data.find("asin(", *n) == *n)
        *n += 4;
    else if (data.find("atan(", *n) == *n)
        *n += 4;
    else
        *parse_error = true;
}

static void validation_tan(const std::string &data, size_t *n, bool *parse_error) {
    if (data.find("tan(", *n) == *n)
        *n += 3;
    else
        *parse_error = true;
}

static void validation_l(const std::string &data, size_t *n, bool *parse_error) {
    if (data.find("ln(", *n) == *n)
        *n += 2;
    else if (data.find("log(", *n) == *n)
        *n += 3;
    else
        *parse_error = true;
}

static void validation_m(const std::string &data, size_t *n, bool *parse_error) {
    if (data.find("mod", *n) == *n)
        *n += 2;
    else
        *parse_error = true;
}

}   // namespace s21
