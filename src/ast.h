#pragma once

#include<iostream>
#include <utility>
#include<vector>
#include<string>
#include<llvm/IR/Value.h>
#include<memory>

extern int dbg_on;

class ExpressionNode;

class VariableDeclarationNode;

class StatementNode;

class CodeGenerationContext;

typedef llvm::Value *ValuePtr;
typedef std::vector<std::shared_ptr<ExpressionNode>> ExpressionList;
typedef std::vector<std::shared_ptr<StatementNode>> StatementList;
typedef std::vector<std::shared_ptr<VariableDeclarationNode>> VariableList;

using std::shared_ptr;
using std::make_shared;


class ASTNode {
public:
    virtual ~ASTNode() = default;

    virtual ValuePtr generateCode(CodeGenerationContext &context) const {
        return nullptr;
    }

    virtual void debugPrint(std::string prefix) const {}

};

class ExpressionNode : public ASTNode {
public:
};

class StatementNode : public ASTNode {
public:
};

class IntegerNode : public ExpressionNode {
public:
    int64_t value;

    explicit IntegerNode(const int64_t &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "IntegerNode( value: " << value << ")\n";
    }
};

class CharNode : public ExpressionNode {
public:
    char value;

    explicit CharNode(const char &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "CharNode( value: " << value << ")\n";
    }
};

class RealNode : public ExpressionNode {
public:
    double value;

    explicit RealNode(const double &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "RealNode( value: " << value << ")\n";
    }
};

class BoolNode : public ExpressionNode {
public:
    bool value;

    explicit BoolNode(const bool &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "BoolNode( value: " << value << ")\n";
    }
};


class IdentifierNode : public ExpressionNode {
public:
    std::string name;
    bool isType = false;
    bool isArray = false;

    shared_ptr<ExpressionList> arraySize = nullptr;

    explicit IdentifierNode(std::string name) : name(std::move(name)) {}

    IdentifierNode(std::string name, ExpressionList *&size) : name(std::move(name)) {
        arraySize = shared_ptr<ExpressionList>(size);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "IdentifierNode( name: " << name << ", isType: " << isType << ", isArray: " << isArray
                  << ")\n";
    }
};

class BinaryOperatorNode : public ExpressionNode {
public:
    shared_ptr<ExpressionNode> leftExpr;
    shared_ptr<ExpressionNode> rightExpr;
    int op;

    BinaryOperatorNode(ExpressionNode *left, int &op, ExpressionNode *right) : op(op) {
        leftExpr = shared_ptr<ExpressionNode>(left);
        rightExpr = shared_ptr<ExpressionNode>(right);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "BinaryOperatorNode( op: " << op << ")\n";
        std::cout << prefix << " LeftExpr:\n";
        leftExpr->debugPrint(prefix + "  ");
        std::cout << prefix << " RightExpr:\n";
        rightExpr->debugPrint(prefix + "  ");
    }
};


class FunctionCallNode : public ExpressionNode {
public:
    const shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionList> args;

    explicit FunctionCallNode(IdentifierNode *id) : id(shared_ptr<IdentifierNode>(id)), args(nullptr) {}

    FunctionCallNode(IdentifierNode *id, ExpressionList *args) : id(shared_ptr<IdentifierNode>(id)),
                                                               args(shared_ptr<ExpressionList>(args)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "FunctionCallNode\n";
        std::cout << prefix << " id:\n";
        id->debugPrint(prefix + "  ");
        std::cout << prefix << " args:\n";
        if (args) {
            for (auto i = 0; i < args->size(); i++) {
                ((*args)[i])->debugPrint(prefix + "  ");
            }
        }
    }
};

class AssignmentNode : public ExpressionNode {
public:
    shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionNode> expr;

    AssignmentNode(IdentifierNode *id, ExpressionNode *expr) {
        this->id = shared_ptr<IdentifierNode>(id);
        this->expr = shared_ptr<ExpressionNode>(expr);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "AssignmentNode\n";
        std::cout << prefix << " id:\n";
        id->debugPrint(prefix + "  ");
        std::cout << prefix << " expr:\n";
        expr->debugPrint(prefix + "  ");
    }

};


class ArrayIndexNode : public ExpressionNode {
public:
    shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionNode> index;

    ArrayIndexNode(IdentifierNode *id, ExpressionNode *index) {
        this->id = shared_ptr<IdentifierNode>(id);
        this->index = shared_ptr<ExpressionNode>(index);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "ArrayIndexNode\n";
        std::cout << prefix << " id:\n";
        id->debugPrint(prefix + "  ");
        std::cout << prefix << " index:\n";
        index->debugPrint(prefix + "  ");
    }
};


class ArrayIndexAssignmentNode : public ExpressionNode {
public:
    shared_ptr<ArrayIndexNode> element;
    shared_ptr<ExpressionNode> expr;

    ArrayIndexAssignmentNode(ArrayIndexNode *element, ExpressionNode *expr) : element(
            shared_ptr<ArrayIndexNode>(element)), expr(shared_ptr<ExpressionNode>(expr)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "ArrayIndexAssignmentNode\n";
        std::cout << prefix << " element:\n";
        element->debugPrint(prefix + "  ");
        std::cout << prefix << " expr:\n";
        expr->debugPrint(prefix + "  ");
    }
};


class BlockNode : public StatementNode {
public:
    StatementList statements;

    BlockNode() = default;

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "BlockNode\n";
        std::cout << prefix << " statements:\n";
        for (auto &stat: statements) {
            stat->debugPrint(prefix + "  ");
        }
    }
};

class VariableDeclarationNode : public StatementNode {
public:
    const shared_ptr<IdentifierNode> type;
    shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionNode> assignmentExpr; //Nullable

    VariableDeclarationNode(IdentifierNode *type, IdentifierNode *id) : type(shared_ptr<IdentifierNode>(type)),
                                                                        id(shared_ptr<IdentifierNode>(id)),
                                                                        assignmentExpr(nullptr) {}

    VariableDeclarationNode(IdentifierNode *type, IdentifierNode *id, ExpressionNode *expr) : type(
            shared_ptr<IdentifierNode>(type)), id(shared_ptr<IdentifierNode>(id)), assignmentExpr(
            shared_ptr<ExpressionNode>(expr)) {}


    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "VariableDeclarationNode\n";
        std::cout << prefix << " type:\n";
        type->debugPrint(prefix + "  ");
        std::cout << prefix << " id:\n";
        id->debugPrint(prefix + "  ");
        if (assignmentExpr) {
            std::cout << prefix << " expr:\n";
            assignmentExpr->debugPrint(prefix + "  ");
        }
    }
};

class ExpressionStatementNode : public StatementNode {
public:
    shared_ptr<ExpressionNode> expr;

    explicit ExpressionStatementNode(ExpressionNode *expr) {
        this->expr = shared_ptr<ExpressionNode>(expr);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "ExpressionStatementNode\n";
        std::cout << prefix << " expr:\n";
        expr->debugPrint(prefix + "  ");
    }

};

class FunctionDeclarationNode : public StatementNode {
public:
    shared_ptr<IdentifierNode> type;
    shared_ptr<IdentifierNode> id;
    shared_ptr<VariableList> args;
    shared_ptr<BlockNode> block;

    FunctionDeclarationNode(IdentifierNode *type, IdentifierNode *id, VariableList *args, BlockNode *block) : type(
            shared_ptr<IdentifierNode>(type)), id(shared_ptr<IdentifierNode>(id)), args(shared_ptr<VariableList>(args)),
                                                                                                              block(shared_ptr<BlockNode>(
                                                                                                                      block)) {
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "FunctionDeclarationNode\n";

        std::cout << prefix << " type:\n";
        if (type) {
            type->debugPrint(prefix + "  ");
        } else {
            std::cout << prefix << "  Void\n";
        }

        std::cout << prefix << " id:\n";
        id->debugPrint(prefix + "  ");

        std::cout << prefix << " args:\n";
        if (args) {
            for (auto i = 0; i < args->size(); i++) {
                ((*args)[i])->debugPrint(prefix + "  ");
            }
        }

        std::cout << prefix << " block:\n";
        block->debugPrint(prefix + "  ");
    }

};


class IfStatementNode : public StatementNode {
public:
    shared_ptr<ExpressionNode> condition;
    shared_ptr<BlockNode> trueBlock;
    shared_ptr<BlockNode> falseBlock;

    IfStatementNode(ExpressionNode *condition, BlockNode *trueBlock, BlockNode *falseBlock) : condition(
            shared_ptr<ExpressionNode>(condition)), trueBlock(shared_ptr<BlockNode>(trueBlock)), falseBlock(
            shared_ptr<BlockNode>(falseBlock)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "IfStatementNode\n";
        std::cout << prefix << " condition:\n";
        condition->debugPrint(prefix + "  ");
        std::cout << prefix << " trueBlock:\n";
        trueBlock->debugPrint(prefix + "  ");
        if (falseBlock) {
            std::cout << prefix << " falseBlock:\n";
            falseBlock->debugPrint(prefix + "  ");
        }
    }

};


class WhileStatementNode : public StatementNode {
public:
    shared_ptr<ExpressionNode> condition;
    shared_ptr<BlockNode> block;

    WhileStatementNode(ExpressionNode *condition, BlockNode *block) : condition(shared_ptr<ExpressionNode>(condition)),
                                                                      block(shared_ptr<BlockNode>(block)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "WhileStatementNode\n";
        std::cout << prefix << " condition:\n";
        condition->debugPrint(prefix + "  ");
        std::cout << prefix << " Block:\n";
        block->debugPrint(prefix + "  ");
    }

};

class ReturnStatementNode : public StatementNode {
public:
    shared_ptr<ExpressionNode> expr;

    explicit ReturnStatementNode(ExpressionNode *expr) : expr(shared_ptr<ExpressionNode>(expr)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(std::string prefix) const override {
        std::cout << prefix << "ReturnStatementNode\n";
        std::cout << prefix << " expr:\n";
        if (expr) {
            expr->debugPrint(prefix + "  ");
        } else {
            std::cout << prefix << "  Null\n";
        }

    }

};

void compile_and_run(BlockNode *program);
