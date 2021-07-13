#pragma once
#include "ConstVisitor.h"
#include <iostream>

class ConstSimplifier {
    public:
    static std::shared_ptr<Expression> traverse(std::shared_ptr<Expression> original) {
        // a const visitor, visitor.changed = false, original.accept(visitor)
        // get a new tree (share_ptr<Expression>)
        // set changed within visitor
        ConstVisitor visitor;
        std::shared_ptr<Expression> simplified = original;
        do {
            visitor.changed = false;
            simplified = simplified->accept(visitor);
        } while(visitor.changed);
        return simplified;
    }
};