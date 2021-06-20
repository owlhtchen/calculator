#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "Expr.h"

class BinaryOp: public Expression {
    protected:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    public:
    BinaryOp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    bool is_const();
};

class Add: public BinaryOp {
    public:
    Add(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
};

class Minus: public BinaryOp {
    public:
    Minus(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
};

class Mul: public BinaryOp {
    public:
    Mul(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
};

class Pow: public BinaryOp {
    // left: base, right: exponent
    public:
    Pow(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
};

class Div: public BinaryOp {
    public:
    // left: numerator, right: denominator
    Div(std::shared_ptr<Expression> numerator, std::shared_ptr<Expression> denominator); 
    std::shared_ptr<Expression> get_derivative();
    std::string to_string();
};
