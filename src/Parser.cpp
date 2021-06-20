#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <cstdio>
#include "Parser.h"
#include "Expr.h"
#include "ConstVar.h"
#include "UnaryFunc.h"
#include "Binary.h"

bool is_int(std::string s) {
    return s.find('.') == std::string::npos;
}

std::shared_ptr<Expression> term(Parser& s) {
    fprintf(stderr, "in term: %s\n", s.current_str().c_str());
    std::shared_ptr<Expression> res = nullptr;
    if(s.current() == '(') {
        s.next();
        res = expr(s);
        s.next();  // eat ')'
    } else {
        if(isdigit(s.current()) > 0) {
            std::string::size_type sz;  
            res = std::make_shared<DoubleConst>(std::stod(s.current_str(), &sz));
            if(is_int(s.current_str().substr(0, sz))) {
                res = std::make_shared<IntConst>(std::stoi(s.current_str(), &sz));
            }
            s.move(sz);
        } else if(isalpha(s.current())) {
            res = std::make_shared<Variable>(s.current());
            s.next();
        } else {
            std::cerr << "unexpected term: " << s.current_str() << "\n";
            exit(1);
        }
    }
    // std::cout << "after term\n";
    return res;    
}

std::shared_ptr<Expression> pow(Parser& s) {
    fprintf(stderr, "in pow: %s\n", s.current_str().c_str());
    std::shared_ptr<Expression> res = term(s);
    // a^b^c means a^(b^c)
    if(!s.end()) {
        if(s.current() == '^') {
            s.next();
            res = std::make_unique<Pow>(res, pow(s));
        }
    }
    return res;
}

std::shared_ptr<Expression> unary(Parser& s) {
    fprintf(stderr, "in unary: %s\n", s.current_str().c_str());
    std::shared_ptr<Expression> res = nullptr;
    if(s.current() == '+') {
        s.next();
        res = std::make_unique<PosUnary>(pow(s));
    } else if(s.current() == '-') {
        s.next();
        res = std::make_unique<NegUnary>(pow(s));        
    } else {
        res = pow(s);
    }
    return res;
}

std::shared_ptr<Expression> factor(Parser& s) {
    fprintf(stderr, "in factor: %s\n", s.current_str().c_str());
    std::shared_ptr<Expression> res = nullptr;
    if(!s.end()) {
        res = unary(s);
    }
    while(!s.end()) {
        if(s.current() == '*') {
            s.next();
            res = std::make_unique<Mul>(res, unary(s));
        } else if(s.current() == '/') {
            s.next();
            res = std::make_unique<Div>(res, unary(s));
        } else if(s.current() == '+' || s.current() == '-' || s.current() == ')') {
            break;
        } else {
            res = unary(s);
        }
    }
    // std::cout << "after factor\n";
    return res;
}

std::shared_ptr<Expression> expr(Parser& s) {
    fprintf(stderr, "in expr: %s\n", s.current_str().c_str());
    std::shared_ptr<Expression> res = nullptr;
    if(!s.end()) {
        res = factor(s);
    }
    while(!s.end()) {
        if(s.current() == '+'){
            s.next();
            res = std::make_unique<Add>(res, factor(s));
        } else if(s.current() == '-') {
            s.next();
            res = std::make_unique<Minus>(res, factor(s));
        } else if(s.current() == ')') {
            break;
        } else {
            res = factor(s);
        }
    }
    // std::cout << "after expr\n";
    return res;
}
