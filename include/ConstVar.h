#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "Expr.h"

class DoubleConst: public Expression {
    double num;
    public:
    DoubleConst(double num);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
};

class IntConst: public Expression {
    int num;
    public:
    IntConst(int num);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
};

class Variable: public Expression {
    char name;
    public:
    Variable(char name);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
};
