#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cassert>
#include <memory>
#include "Expr.h"

struct Parser {
    std::string s;
    size_t start;

    Parser(std::string _s): s(_s), start(0) {}
    char current() {
        assert(start < s.length());
        return s.at(start);
    }
    bool end() {
        return start == s.length();
    }
    void next() {
        start++;
    }
    void move(size_t diff){
        start += diff;
    }
    std::string current_str() {
        return s.substr(start);
    }
};

std::shared_ptr<Expression> term(Parser& s);
std::shared_ptr<Expression> factor(Parser& s);
std::shared_ptr<Expression> expr(Parser& s);

