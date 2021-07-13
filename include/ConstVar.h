#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "Expr.h"

class Const: public Expression {
    public:
    virtual double getNum() = 0;
};

class DoubleConst: public Expression {
    public:
    double num;
    DoubleConst(double num);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
    std::shared_ptr<Expression> accept(Visitor&  visitor);
    double getNum() {
        return num;
    }
};

class IntConst: public Expression {
    public:
    int num;
    IntConst(int num);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
    std::shared_ptr<Expression> accept(Visitor&  visitor);
    double getNum() {
        return num;
    }
};

class Variable: public Expression {
    public:
    char name;
    Variable(char name);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
    std::shared_ptr<Expression> accept(Visitor&  visitor);
};
