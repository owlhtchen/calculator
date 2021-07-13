#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "Expr.h"

class Visitor;
class PosUnary: public Expression {
    public:
    std::shared_ptr<Expression> right;
    PosUnary(std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
    std::shared_ptr<Expression> accept(Visitor&  visitor);
};

class NegUnary: public Expression {
    public:
    std::shared_ptr<Expression> right;
    NegUnary(std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
    std::shared_ptr<Expression> accept(Visitor&  visitor);
};

class LnFunc: public Expression {
    public:
    std::shared_ptr<Expression> right;
    LnFunc(std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
    bool is_const();
    std::shared_ptr<Expression> accept(Visitor&  visitor);
};
