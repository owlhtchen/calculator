#include <iostream>
#include <memory>
#include <string>
#include "Parser.h"
#include "Expr.h"

std::string get_tree_str(std::string s) {
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    auto parser = Parser(s);
    auto tree = expr(parser);
    return tree->to_string();
}

void test_print_tree() {
    // s consists of digits, '+', '-', '(', ')', ' ' and '^'.
    // std::string s = "3 * x * y + 4";
    // std::string s = "a^b^c"; // a^(b^c)
    // std::string s = "x^2";
    // std::string s = "a*b/c/d"; // ((a*b)/c)/d
    std::string s = "3 * x * (y + 4^3^5)";
    auto str_tree = get_tree_str(s);
    std::cout << "-- print tree 1\n";
    std::cout << str_tree << std::endl;
    // s = "3 * x * (y + 4)";
    // str_tree = get_tree_str(s);
    // std::cout << "-- print tree 2\n";
    // std::cout << str_tree << std::endl;
}

int main() {
    // std::string s = "3 * x^2 ";
    // std::string s = "(3 * x)^2 ";
    // std::string s = "1/3";
    // std::string s = "((4*-x)^2 + x) * (x^3 + 1)";
    // std::string s = "2 ^ x";
    std::string s = "x ^ x";
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    auto parser = Parser(s);
    auto tree = expr(parser);
    auto derivative = tree->get_derivative();
    std::cout << "-- derivative tree:\n";
    std::cout << derivative->to_string() << std::endl;
    return 0;
}