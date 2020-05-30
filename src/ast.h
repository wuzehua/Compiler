#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include <llvm/IR/Value.h>

#include <functional>

//#include "context.h"

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
    ASTNode *parent = nullptr;

    [[nodiscard]] virtual std::vector<ASTNode *> getChildren() const {
        return std::vector<ASTNode *>(0);
    }

    [[nodiscard]] virtual ASTNode *getChildren(int index) const {
        return getChildren()[index];
    }

    [[nodiscard]] virtual int getChildrenNumber() const {
        return getChildren().size();
    }

    [[nodiscard]] virtual std::string getLabel() const {
        return "";
    }

    [[nodiscard]] virtual std::string getDescription() const {
        return "";
    }

    virtual ~ASTNode() = default;

    virtual ValuePtr generateCode(CodeGenerationContext &context) const {
        return nullptr;
    }

    virtual void debugPrint(const std::string &prefix) const {}

};

class ExpressionNode : public ASTNode {
public:

    [[nodiscard]] std::string getLabel() const override {
        return "ExpressionNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }
};

class StatementNode : public ASTNode {
public:

    [[nodiscard]] std::string getLabel() const override {
        return "StatementNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }
};

class IntegerNode : public ExpressionNode {
public:
    int64_t value;

    [[nodiscard]] std::string getLabel() const override {
        return "IntegerNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "value: " + std::to_string(value);
    }

    explicit IntegerNode(const int64_t &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "IntegerNode( value: " << value << ")\n";
    }
};

class CharNode : public ExpressionNode {
public:
    char value;

    [[nodiscard]] std::string getLabel() const override {
        return "CharNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "value: " + std::to_string(value);
    }

    explicit CharNode(const char &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "CharNode( value: " << value << ")\n";
    }
};

class RealNode : public ExpressionNode {
public:
    double value;

    [[nodiscard]] std::string getLabel() const override {
        return "RealNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "value: " + std::to_string(value);
    }

    explicit RealNode(const double &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "RealNode( value: " << value << ")\n";
    }
};

class BoolNode : public ExpressionNode {
public:
    bool value;

    [[nodiscard]] std::string getLabel() const override {
        return "BoolNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "value: " + std::to_string(value);
    }

    explicit BoolNode(const bool &value) : value(value) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "BoolNode( value: " << value << ")\n";
    }
};


class TypeNode : public ExpressionNode {
public:
    std::string name;
    bool isArray = false;

    shared_ptr<IntegerNode> arraySize = nullptr;

    [[nodiscard]] std::string getLabel() const override {
        return "TypeNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "name: " + name + "\tisArray: " + std::to_string(isArray);
    }

    explicit TypeNode(std::string name) : name(std::move(name)) {}

    TypeNode(std::string name, IntegerNode *&size) : name(std::move(name)), arraySize(size) {}

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "TypeNode( name: " << name << ", isArray: " << isArray << ")\n";
    }
};


class IdentifierNode : public ExpressionNode {
public:
    std::string name;

    [[nodiscard]] std::string getLabel() const override {
        return "IdentifierNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "name: " + name;
    }

    explicit IdentifierNode(std::string name) : name(std::move(name)) {}


    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "IdentifierNode( name: " << name << ")\n";
    }
};

class BinaryOperatorNode : public ExpressionNode {
public:
    shared_ptr<ExpressionNode> leftExpr;
    shared_ptr<ExpressionNode> rightExpr;
    int op;

    [[nodiscard]] std::string getLabel() const override {
        return "BinaryOperatorNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "op: " + std::to_string(op);
    }

    BinaryOperatorNode(ExpressionNode *left, int &op, ExpressionNode *right) : op(op) {
        leftExpr = shared_ptr<ExpressionNode>(left);
        rightExpr = shared_ptr<ExpressionNode>(right);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "FunctionCallNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    explicit FunctionCallNode(IdentifierNode *id) : id(shared_ptr<IdentifierNode>(id)), args(nullptr) {}

    FunctionCallNode(IdentifierNode *id, ExpressionList *args) : id(shared_ptr<IdentifierNode>(id)),
                                                                 args(shared_ptr<ExpressionList>(args)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "AssignmentNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    AssignmentNode(IdentifierNode *id, ExpressionNode *expr) {
        this->id = shared_ptr<IdentifierNode>(id);
        this->expr = shared_ptr<ExpressionNode>(expr);
    }

    AssignmentNode(shared_ptr<IdentifierNode> id, shared_ptr<ExpressionNode> expr) : id(std::move(id)),
                                                                                     expr(std::move(expr)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "ArrayIndexNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    ArrayIndexNode(IdentifierNode *id, ExpressionNode *index) {
        this->id = shared_ptr<IdentifierNode>(id);
        this->index = shared_ptr<ExpressionNode>(index);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "ArrayIndexAssignmentNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    ArrayIndexAssignmentNode(ArrayIndexNode *element, ExpressionNode *expr) : element(
            shared_ptr<ArrayIndexNode>(element)), expr(shared_ptr<ExpressionNode>(expr)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "BlockNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    BlockNode() = default;

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "BlockNode\n";
        std::cout << prefix << " statements:\n";
        for (auto &stat: statements) {
            stat->debugPrint(prefix + "  ");
        }
    }
};

class VariableDeclarationNode : public StatementNode {
public:
    shared_ptr<TypeNode> type;
    shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionNode> assignmentExpr; //Nullable

    [[nodiscard]] std::string getLabel() const override {
        return "VariableDeclarationNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    VariableDeclarationNode(TypeNode *type, IdentifierNode *id) : type(shared_ptr<TypeNode>(type)),
                                                                  id(shared_ptr<IdentifierNode>(id)),
                                                                  assignmentExpr(nullptr) {}

    VariableDeclarationNode(TypeNode *type, IdentifierNode *id, ExpressionNode *expr) : type(
            shared_ptr<TypeNode>(type)), id(shared_ptr<IdentifierNode>(id)), assignmentExpr(
            shared_ptr<ExpressionNode>(expr)) {}


    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "ExpressionStatementNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    explicit ExpressionStatementNode(ExpressionNode *expr) {
        this->expr = shared_ptr<ExpressionNode>(expr);
    }

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "ExpressionStatementNode\n";
        std::cout << prefix << " expr:\n";
        expr->debugPrint(prefix + "  ");
    }

};

class FunctionDeclarationNode : public StatementNode {
public:
    shared_ptr<TypeNode> type;
    shared_ptr<IdentifierNode> id;
    shared_ptr<VariableList> args;
    shared_ptr<BlockNode> block;
    bool external;

    [[nodiscard]] std::string getLabel() const override {
        return "FunctionDeclarationNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    FunctionDeclarationNode(TypeNode *type, IdentifierNode *id, VariableList *args, BlockNode *block,
                            bool external = false) : type(shared_ptr<TypeNode>(type)),
                                                     id(shared_ptr<IdentifierNode>(id)),
                                                     args(shared_ptr<VariableList>(args)),
                                                     block(shared_ptr<BlockNode>(block)), external(external) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "IfStatementNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    IfStatementNode(ExpressionNode *condition, BlockNode *trueBlock, BlockNode *falseBlock) : condition(
            shared_ptr<ExpressionNode>(condition)), trueBlock(shared_ptr<BlockNode>(trueBlock)), falseBlock(
            shared_ptr<BlockNode>(falseBlock)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "WhileStatementNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    WhileStatementNode(ExpressionNode *condition, BlockNode *block) : condition(shared_ptr<ExpressionNode>(condition)),
                                                                      block(shared_ptr<BlockNode>(block)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
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

    [[nodiscard]] std::string getLabel() const override {
        return "ReturnStatementNode";
    }

    [[nodiscard]] std::string getDescription() const override {
        return "";
    }

    explicit ReturnStatementNode(ExpressionNode *expr) : expr(shared_ptr<ExpressionNode>(expr)) {}

    ValuePtr generateCode(CodeGenerationContext &context) const override;

    void debugPrint(const std::string &prefix) const override {
        std::cout << prefix << "ReturnStatementNode\n";
        std::cout << prefix << " expr:\n";
        if (expr) {
            expr->debugPrint(prefix + "  ");
        } else {
            std::cout << prefix << "  Null\n";
        }

    }

};
