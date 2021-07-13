#pragma once

#include <memory>
#include "Expr.h"
#include "ConstVar.h"
#include "UnaryFunc.h"
#include "Binary.h"
#include "Visitor.h"
#include "Util.h"

class ConstVisitor:public Visitor {
    public:
    bool changed;
    ConstVisitor(): changed(false) { };
    std::shared_ptr<Expression> visit(std::shared_ptr<DoubleConst> expr) {
        return expr->shared_from_this();
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<IntConst> expr) {
        return expr->shared_from_this();
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<Variable> expr) {
        return expr->shared_from_this();
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<PosUnary> expr) {
        auto sp_right = expr->right->accept(*this);   
        changed = true;
        return sp_right;  
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<NegUnary> expr) {
        auto sp_right = expr->right->accept(*this);
        // to int
        auto right_i = std::dynamic_pointer_cast<IntConst>(sp_right);
        if(right_i) {
            return std::make_shared<IntConst>(-right_i->num);
        }
        // to double
        auto right_f = std::dynamic_pointer_cast<DoubleConst>(sp_right);
        if(right_f) {
            return std::make_shared<DoubleConst>(-right_f->num);
        }    
        // -- -> +
        auto right_neg = std::dynamic_pointer_cast<NegUnary>(sp_right);
        if(right_neg) {
            return right_neg->right;
        }  
        return std::make_shared<NegUnary>(sp_right); 
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<LnFunc> expr) {
        auto sp_right = expr->right->accept(*this);
        return std::make_shared<LnFunc>(sp_right);
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<Add> expr) {
        auto sp_left = expr->left->accept(*this);
        auto sp_right = expr->right->accept(*this);
        // to int
        auto left_i = std::dynamic_pointer_cast<IntConst>(sp_left); 
        auto right_i = std::dynamic_pointer_cast<IntConst>(sp_right); 
        if(left_i && right_i) {
            changed = true;
            return std::make_shared<IntConst>(left_i->num + right_i->num);
        } else if((left_i && (0 == left_i->num))) {
            changed = true;
            return sp_right;
        } else if((right_i && (0 == right_i->num))) {
            changed = true;
            return sp_left;
        }
        // to double / int
        auto left_c = std::dynamic_pointer_cast<Const>(sp_left); 
        auto right_c = std::dynamic_pointer_cast<Const>(sp_right); 
        if((left_c && right_c)) {
            changed = true;
            return std::make_shared<DoubleConst>(left_c->getNum() + right_c->getNum());
        } else if((left_c && (isNearlyZero(left_c->getNum())))) {
            changed = true;
            return sp_right;
        } else if((right_c && (isNearlyZero(right_c->getNum())))) {
            changed = true;
            return sp_left;
        }
        return std::make_shared<Add>(sp_left, sp_right);
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<Minus> expr) {
        auto sp_left = expr->left->accept(*this);
        auto sp_right = expr->right->accept(*this);
        // to int
        auto left_i = std::dynamic_pointer_cast<IntConst>(sp_left); 
        auto right_i = std::dynamic_pointer_cast<IntConst>(sp_right); 
        if(left_i && right_i) {
            changed = true;
            return std::make_shared<IntConst>(left_i->num - right_i->num);
        } else if((left_i && (0 == left_i->num))) {
            changed = true;
            return std::make_shared<NegUnary>(right_i);
        } else if((right_i && (0 == right_i->num))) {
            changed = true;
            return sp_left;
        }
        // to double
        auto left_d = std::dynamic_pointer_cast<Const>(sp_left); 
        auto right_d = std::dynamic_pointer_cast<Const>(sp_right); 
        if((left_d && right_d)) {
            changed = true;
            return std::make_shared<DoubleConst>(left_d->getNum() - right_d->getNum());
        } else if((left_d && (isNearlyZero(left_d->getNum())))) {
            changed = true;
            return std::make_shared<NegUnary>(sp_right);
        } else if((right_d && (isNearlyZero(right_d->getNum())))) {
            changed = true;
            return sp_left;
        }
        return std::make_shared<Minus>(sp_left, sp_right);
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<Mul> expr) {
        auto sp_left = expr->left->accept(*this);
        auto sp_right = expr->right->accept(*this);
        // to int
        auto left_i = std::dynamic_pointer_cast<IntConst>(sp_left); 
        auto right_i = std::dynamic_pointer_cast<IntConst>(sp_right); 
        if(left_i && right_i) {
            changed = true;
            return std::make_shared<IntConst>(left_i->num * right_i->num);
        } else if((left_i && (0 == left_i->num))) {
            changed = true;
            return std::make_shared<IntConst>(0);
        } else if((right_i && (0 == right_i->num))) {
            changed = true;
            return std::make_shared<IntConst>(0);
        } else if((left_i && (1 == left_i->num))) {
            changed = true;
            return sp_right;
        } else if((right_i && (1 == right_i->num))) {
            changed = true;
            return sp_left;
        }
        // to double
        auto left_d = std::dynamic_pointer_cast<DoubleConst>(sp_left); 
        auto right_d = std::dynamic_pointer_cast<DoubleConst>(sp_right); 
        if((left_d && right_d)) {
            changed = true;
            return std::make_shared<DoubleConst>(left_d->getNum() * right_d->getNum());
        } else if((left_d && (isNearlyZero(left_d->num)))) {
            changed = true;
            return std::make_shared<DoubleConst>(0);
        } else if((right_d && (isNearlyZero(right_d->num)))) {
            changed = true;
            return std::make_shared<DoubleConst>(0);
        } else if((left_d && (isEqual(left_i->num, 1.0)))) {
            changed = true;
            return sp_right;
        } else if((right_d && (isEqual(right_i->num, 1.0)))) {
            changed = true;
            return sp_left;
        }
        return std::make_shared<Mul>(sp_left, sp_right);
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<Pow> expr) {
        auto base = expr->left->accept(*this);
        auto pow = expr->right->accept(*this);
        // to int
        auto pow_i = std::dynamic_pointer_cast<IntConst>(pow);
        if(pow_i && 0 == pow_i->num ) {
            changed = true;
            return std::make_shared<IntConst>(1);
        } else if(pow_i && 1 == pow_i->num ) {
            changed = true;
            return base;
        }
        // to double
        auto pow_d = std::dynamic_pointer_cast<DoubleConst>(pow);
        if(pow_d && isEqual(pow_d->num, 0.0) ) {
            changed = true;
            return std::make_shared<IntConst>(1);
        } else if(pow_d && isEqual(pow_d->num, 1.0)  ) {
            changed = true;
            return base;
        }        
        return std::make_shared<Pow>(base, pow);
    }
    std::shared_ptr<Expression> visit(std::shared_ptr<Div> expr) {
        auto sp_left = expr->left->accept(*this);
        auto sp_right = expr->right->accept(*this);
        // to int
        auto left_i = std::dynamic_pointer_cast<IntConst>(sp_left); 
        auto right_i = std::dynamic_pointer_cast<IntConst>(sp_right); 
        if(left_i && right_i) {
            changed = true;
            if(0 == left_i->num % right_i->num) {
                return std::make_shared<IntConst>(left_i->num / right_i->num);
            } else {
                return std::make_shared<DoubleConst>((double) left_i->num / right_i->num);
            }
        } else if((left_i && (0 == left_i->num))) {
            changed = true;
            return std::make_shared<IntConst>(0);
        } else if((right_i && (1 == right_i->num))) {
            changed = true;
            return sp_left;
        }
        // to double
        auto left_d = std::dynamic_pointer_cast<DoubleConst>(sp_left); 
        auto right_d = std::dynamic_pointer_cast<DoubleConst>(sp_right); 
        if((left_d && right_d)) {
            changed = true;
            return std::make_shared<DoubleConst>(left_d->getNum() / right_d->getNum());
        } else if((left_d && (isNearlyZero(left_d->num)))) {
            changed = true;
            return std::make_shared<DoubleConst>(0);
        } else if((right_d && (isEqual(right_i->num, 1.0)))) {
            changed = true;
            return sp_left;
        }
        return std::make_shared<Div>(sp_left, sp_right);       
    }
};
