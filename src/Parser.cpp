#include <iostream>
#include <string>
#include <cctype>
#include "Parser.h"
#include <memory>

// std::shared_ptr<Expression> term(Parser& s) {
//     // (expr) +10 -10 10
//     std::shared_ptr<Expression> res = nullptr;
//     if(s.current() == '(') {
//         s.next();
//         res = expr(s);
//         s.next();  // eat ')'
//     } else {
//         if(s.current() == '+' || s.current() == '-' || isdigit(s.current()) > 0) {
//             std::string::size_type sz;  
//             res = std::make_shared<Constant>(std::stod (s.current_str(), &sz));
//             s.move(sz);
//         } else {
//             std::cerr << "unexpected term: " << s.current_str() << "\n";
//         }
//     }
//     // std::cout << "after term\n";
//     return res;
// }

std::shared_ptr<Expression> term(Parser& s) {
    std::shared_ptr<Expression> res = nullptr;
    if(s.current() == '(') {
        s.next();
        res = expr(s);
        s.next();  // eat ')'
    } else {
        if(isdigit(s.current()) > 0) {
            std::string::size_type sz;  
            res = std::make_shared<Constant>(std::stod (s.current_str(), &sz));
            s.move(sz);
        } else if(isalpha(s.current())) {
            res = std::make_shared<Variable>(s.current());
            s.next();
        } else {
            std::cerr << "unexpected term: " << s.current_str() << "\n";
        }
    }
    // std::cout << "after term\n";
    return res;    
}

std::shared_ptr<Expression> pow(Parser& s) {
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
    std::shared_ptr<Expression> res = nullptr;
    if(!s.end()) {
        res = term(s);
    }
    while(!s.end()) {
        if(s.current() == '*') {
            s.next();
            res = std::make_unique<Mul>(res, term(s));
        } else if(s.current() == '/') {
            s.next();
            res = std::make_unique<Div>(res, term(s));
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
            res = std::make_unique<Add>(res, factor(s));
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
