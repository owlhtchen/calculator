#pragma once

#include <memory>
#include "Expr.h"
#include "ConstVar.h"
#include "UnaryFunc.h"
#include "Binary.h"

class Visitor {
    public:
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<DoubleConst> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<IntConst> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<Variable> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<PosUnary> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<NegUnary> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<LnFunc> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<Add> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<Minus> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<Mul> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<Pow> expr) = 0;
    virtual std::shared_ptr<Expression> visit(std::shared_ptr<Div> expr) = 0;
};