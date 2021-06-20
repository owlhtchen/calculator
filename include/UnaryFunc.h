#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "Expr.h"

class PosUnary: public Expression {
    std::shared_ptr<Expression> right;
    public:
    PosUnary(std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
};

class NegUnary: public Expression {
    std::shared_ptr<Expression> right;
    public:
    NegUnary(std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
};

class LnFunc: public Expression {
    std::shared_ptr<Expression> right;
    public:
    LnFunc(std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
};
