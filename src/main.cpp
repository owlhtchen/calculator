#include <iostream>
#include <memory>
#include <string>
#include "Parser.h"
#include "Expr.h"


int main() {
    // s consists of digits, '+', '-', '(', ')', and ' '.
    std::string s = "3 * 3 + 4";
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    auto parser = Parser(s);
    auto tree = expr(parser);
    auto str_tree = tree->to_string();
    std::cout << str_tree << std::endl;
    return 0;
}