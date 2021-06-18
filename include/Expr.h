#ifndef EXPR_H
#define EXPR_H
#include <iostream>
#include <memory>
#include <string>

class Expression{

    public:
    virtual std::shared_ptr<Expression> get_derivative()=0;
    virtual std::string to_string()=0;
};

class Constant: public Expression {
    double num;
    public:
    Constant(double num): num(num) {};
    std::shared_ptr<Expression> get_derivative() {
        return std::make_shared<Constant>(0);
    }
    std::string to_string() {
        return std::to_string(num);
    }
};

class Variable: public Expression {
    char name;
    public:
    Variable(double name): name(name) {};
    std::shared_ptr<Expression> get_derivative() {
        return std::make_shared<Constant>(1);
    }
    std::string to_string() {
        return std::string(1, name);
    }
};

// class UnaryOp {
    
// };

class BinaryOp: public Expression {
    protected:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    public:
    BinaryOp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        left(left), right(right) { };
};

class Plus: public BinaryOp {
    public:
    Plus(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };
    std::shared_ptr<Expression> get_derivative() {
        return std::make_shared<Plus>(left->get_derivative(), right->get_derivative());
    }    
    std::string to_string() {
        return " (" + left->to_string() + " + "  + right->to_string() + ") ";
    }
};

class Minus: public BinaryOp {
    public:
    Minus(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };
    std::shared_ptr<Expression> get_derivative() {
        return std::make_shared<Minus>(left->get_derivative(), right->get_derivative());
    }    
    std::string to_string() {
        return " (" + left->to_string() + " - "  + right->to_string() + ") ";
    }    
};

class Mul: public BinaryOp {
    public:
    Mul(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };
    std::shared_ptr<Expression> get_derivative() {
        auto deriv_first = std::make_shared<Mul>(left->get_derivative(), right);
        auto deriv_second = std::make_shared<Mul>(left, right->get_derivative());
        return std::make_shared<Plus>(deriv_first, deriv_second);
    } 
    std::string to_string() {
        return " (" + left->to_string() + " * "  + right->to_string() + ") ";
    }           
};

class Pow: public BinaryOp {
    // left: base, right: exponent
    public:
    Pow(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };    
    std::shared_ptr<Expression> get_derivative() {
        auto new_exp = std::make_shared<Minus>(right, std::make_shared<Constant>(1));
        auto new_pow = std::make_shared<Pow>(left, new_exp);
        return std::make_shared<Mul>(right, new_pow);
    }
    std::string to_string() {
        return " (" + left->to_string() + " ^ "  + right->to_string() + ") ";
    }    
};

class Div: public BinaryOp {
    public:
    // left: numerator, right: denominator
    Div(std::shared_ptr<Expression> numerator, std::shared_ptr<Expression> denominator):
        BinaryOp(numerator, denominator) { }; 
    std::shared_ptr<Expression> get_derivative() {
        auto numer_first = std::make_shared<Mul>(left->get_derivative(), right);
        auto numer_second = std::make_shared<Mul>(left, right->get_derivative());
        auto numerator = std::make_shared<Minus>(numer_first, numer_second);
        auto denominator = std::make_shared<Pow>(right, std::make_shared<Constant>(2));
        return std::make_shared<Div>(numerator, denominator);
    }   
    std::string to_string() {
        return " (" + left->to_string() + " / "  + right->to_string() + ") ";
    }    
};
#endif