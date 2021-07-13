#include <iostream>
#include <memory>
#include <string>
#include "Expr.h"
#include "ConstVar.h"
#include "UnaryFunc.h"
#include "Binary.h"
#include "Visitor.h"

// class Expression{

//     public:
//     virtual std::shared_ptr<Expression> get_derivative()=0;
//     virtual std::string to_string()=0;
//     virtual bool is_const() = 0;
// };

// class DoubleConst: public Expression {
//     double num;
//     public:
    DoubleConst::DoubleConst(double num): num(num) {};
    std::shared_ptr<Expression> DoubleConst::get_derivative() {
        return std::make_shared<DoubleConst>(0);
    }
    std::string DoubleConst::to_string() {
        return std::to_string(num);
    }
    bool DoubleConst::is_const() {
        return true;
    }
    std::shared_ptr<Expression> DoubleConst::accept(Visitor&  visitor) {
        return  visitor.visit(shared_from_base<DoubleConst>());
    }
// };

// class IntConst: public Expression {
//     int num;
//     public:
    IntConst::IntConst(int num): num(num) {};
    std::shared_ptr<Expression> IntConst::get_derivative() {
        return std::make_shared<IntConst>(0);
    }
    std::string IntConst::to_string() {
        return std::to_string(num);
    }
    bool IntConst::is_const() {
        return true;
    }
    std::shared_ptr<Expression> IntConst::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<IntConst>());
    }    
// };

// class Variable: public Expression {
//     char name;
//     public:
    Variable::Variable(char name): name(name) {};
    std::shared_ptr<Expression> Variable::get_derivative() {
        return std::make_shared<IntConst>(1);
    }
    std::string Variable::to_string() {
        return std::string(1, name);
    }
    bool Variable::is_const() {
        return false;
    }
    std::shared_ptr<Expression> Variable::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<Variable>());
    }
// };

// class PosUnary: public Expression {
//     std::shared_ptr<Expression> right;
//     public:
    PosUnary::PosUnary(std::shared_ptr<Expression> right): right(right) { };
    std::shared_ptr<Expression> PosUnary::get_derivative() {
        return std::make_shared<IntConst>(1);
    }
    std::string PosUnary::to_string() {
        return " +" + right->to_string();
    }    
    bool PosUnary::is_const() {
        return right->is_const();
    }
    std::shared_ptr<Expression> PosUnary::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<PosUnary>());
    } 
// };

// class NegUnary: public Expression {
//     std::shared_ptr<Expression> right;
//     public:
    NegUnary::NegUnary(std::shared_ptr<Expression> right): right(right) { };
    std::shared_ptr<Expression> NegUnary::get_derivative() {
        return std::make_shared<IntConst>(-1);
    }    
    std::string NegUnary::to_string() {
        return " -" + right->to_string();
    } 
    bool NegUnary::is_const() {
        return right->is_const();
    }
    std::shared_ptr<Expression> NegUnary::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<NegUnary>());
    } 
// };

// class LnFunc: public Expression {
//     std::shared_ptr<Expression> right;
//     public:
    LnFunc::LnFunc(std::shared_ptr<Expression> right): right(right) { };
    std::shared_ptr<Expression> LnFunc::get_derivative() {
        auto no_chained = std::make_shared<Div>(std::make_shared<IntConst>(1), right);
        auto chained = std::make_shared<Mul>(no_chained, right->get_derivative());
        return chained;
    }    
    std::string LnFunc::to_string() {
        return " ln(" + right->to_string() + ") ";
    } 
    bool LnFunc::is_const() {
        return right->is_const();
    }
    std::shared_ptr<Expression> LnFunc::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<LnFunc>());
    }    
// };

// class BinaryOp: public Expression {
//     protected:
//     std::shared_ptr<Expression> left;
//     std::shared_ptr<Expression> right;
//     public:
    BinaryOp::BinaryOp(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        left(left), right(right) { };
    bool BinaryOp::is_const() {
        return left->is_const() && right->is_const();
    }
// };

// class Add: public BinaryOp {
//     public:
    Add::Add(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };
    std::shared_ptr<Expression> Add::get_derivative() {
        return std::make_shared<Add>(left->get_derivative(), right->get_derivative());
    }    
    std::string Add::to_string() {
        return " (" + left->to_string() + " + "  + right->to_string() + ") ";
    }
    std::shared_ptr<Expression> Add::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<Add>());
    }    
// };

// class Minus: public BinaryOp {
//     public:
    Minus::Minus(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };
    std::shared_ptr<Expression> Minus::get_derivative() {
        return std::make_shared<Minus>(left->get_derivative(), right->get_derivative());
    }    
    std::string Minus::to_string() {
        return " (" + left->to_string() + " - "  + right->to_string() + ") ";
    } 
    std::shared_ptr<Expression> Minus::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<Minus>());
    }
// };

// class Mul: public BinaryOp {
//     public:
    Mul::Mul(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };
    std::shared_ptr<Expression> Mul::get_derivative() {
        auto deriv_first = std::make_shared<Mul>(left->get_derivative(), right);
        auto deriv_second = std::make_shared<Mul>(left, right->get_derivative());
        return std::make_shared<Add>(deriv_first, deriv_second);
    } 
    std::string Mul::to_string() {
        return " (" + left->to_string() + " * "  + right->to_string() + ") ";
    }      
    std::shared_ptr<Expression> Mul::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<Mul>());
    }         
// };

// class Pow: public BinaryOp {
//     // left: base, right: exponent
//     public:
    Pow::Pow(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        BinaryOp(left, right) { };    
    std::shared_ptr<Expression> Pow::get_derivative() {
        std::shared_ptr<Expression> res = nullptr;
        if(left->is_const() && right->is_const()){
            res = std::make_shared<IntConst>(0);
        } else if(right->is_const()) { // x^2
            auto new_exp = std::make_shared<Minus>(right, std::make_shared<IntConst>(1));
            auto new_pow = std::make_shared<Pow>(left, new_exp);
            auto no_chained = std::make_shared<Mul>(right, new_pow);
            auto chained = left->get_derivative();
            res = std::make_shared<Mul>(no_chained, chained);
        } else if(left->is_const()) { 
            auto eff = std::make_shared<LnFunc>(left);
            // std::shared_ptr<Expression>(this)
            /*
            struct shared_ptr{
                T* data;  
                ControlBlock * cb;
            };
            ControlBlock{
                int ref_count;
            };
            */
            res = std::make_shared<Mul>(this->shared_from_this(), eff);
        } else {
            auto first_part = std::make_shared<Mul>(right->get_derivative(), 
                std::make_shared<LnFunc>(left));
            auto second_part = std::make_shared<Mul>(right, 
                std::make_shared<Div>(left->get_derivative(), left));
            res = std::make_shared<Mul>(this->shared_from_this(),
                std::make_shared<Add>(first_part, second_part));
        }
        return res;
    }
    std::string Pow::to_string() {
        return " (" + left->to_string() + " ^ "  + right->to_string() + ") ";
    } 
    std::shared_ptr<Expression> Pow::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<Pow>());
    }       
// };

// class Div: public BinaryOp {
//     public:
    // left: numerator, right: denominator
    Div::Div(std::shared_ptr<Expression> numerator, std::shared_ptr<Expression> denominator):
        BinaryOp(numerator, denominator) { }; 
    std::shared_ptr<Expression> Div::get_derivative() {
        auto numer_first = std::make_shared<Mul>(left->get_derivative(), right);
        auto numer_second = std::make_shared<Mul>(left, right->get_derivative());
        auto numerator = std::make_shared<Minus>(numer_first, numer_second);
        auto denominator = std::make_shared<Pow>(right, std::make_shared<DoubleConst>(2));
        return std::make_shared<Div>(numerator, denominator);
    }   
    std::string Div::to_string() {
        return " (" + left->to_string() + " / "  + right->to_string() + ") ";
    }  
    std::shared_ptr<Expression> Div::accept(Visitor&  visitor) {
        return visitor.visit(shared_from_base<Div>());
    }      
// };