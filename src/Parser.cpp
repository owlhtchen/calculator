#include <iostream>
#include <string>
#include <cctype>
#include "Parser.h"
#include <memory>

std::shared_ptr<Expression> term(Parser& s) {
    // (expr) +10 -10 10
    std::shared_ptr<Expression> res = nullptr;
    if(s.current() == '(') {
        s.next();
        res = expr(s);
        s.next();  // eat ')'
    } else {
        if(s.current() == '+' || s.current() == '-' || isdigit(s.current()) > 0) {
            std::string::size_type sz;  
            res = std::make_shared<Constant>(std::stod (s.current_str(), &sz));
            s.move(sz);
        } else {
            std::cerr << "unexpected term: " << s.current_str() << "\n";
        }
    }
    // std::cout << "after term\n";
    return res;
}

std::shared_ptr<Expression> factor(Parser& s) {
    std::shared_ptr<Expression> res = nullptr;
    if(!s.end()) {
        res = term(s);
    }
    while(!s.end()) {
        if(s.current() == '*') {
            s.next();
            res = std::make_unique<Mul>(res, factor(s));
        } else if(s.current() == '/') {
            s.next();
            res = std::make_unique<Div>(res, factor(s));
        } else {
            break;
        }
    }
    // std::cout << "after factor\n";
    return res;
}

std::shared_ptr<Expression> expr(Parser& s) {
    std::shared_ptr<Expression> res = nullptr;
    if(!s.end()) {
        res = factor(s);
    }
    while(!s.end()) {
        if(s.current() == '+'){
            s.next();
            res = std::make_unique<Plus>(res, factor(s));
        } else if(s.current() == '-') {
            s.next();
            res = std::make_unique<Minus>(res, factor(s));
        } else {
            break;
        }
    }
    // std::cout << "after expr\n";
    return res;
}
