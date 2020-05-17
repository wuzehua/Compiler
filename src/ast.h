#include<iostream>
#include<vector>
#include<string>
#include<llvm/IR/Value.h>
#include<memory>


class ExpressionNode;
class VariableDeclarationNode;
class StatementNode;
class CodeGenerationContext;

typedef llvm::Value* ValuePtr;
typedef std::vector<std::shared_ptr<ExpressionNode>> ExpressionList;
typedef std::vector<std::shared_ptr<StatementNode>> StatementList;
typedef std::vector<std::shared_ptr<VariableDeclarationNode>> VariableList;


class ASTNode{
public:
    virtual ~ASTNode(){}
    virtual ValuePtr generateCode(CodeGenerationContext& context){
        return nullptr;
    }
};

class ExpressionNode: public ASTNode{
public:
};

class StatementNode: public ASTNode{
public:
};

class IntegerNode: public ExpressionNode{
public:
    int64_t value;
    IntegerNode(const int64_t& value): value(value){}
    ValuePtr generateCode(CodeGenerationContext& context);
};

class CharNode: public ExpressionNode{
public:
    char value;
    CharNode(const char& value): value(value){}
    ValuePtr generateCode(CodeGenerationContext& context);
};

class RealNode: public ExpressionNode{
public:
    double value;
    RealNode(const double& value): value(value){}
    ValuePtr generateCode(CodeGenerationContext& context);
};


class IdentifierNode: public ExpressionNode{
public:
    std::string name;
    IdentifierNode(const std::string& name): name(name){}
    ValuePtr generateCode(CodeGenerationContext& context);
};

class BinaryOperatorNode: public ExpressionNode{
public:
    ExpressionNode& leftExpr;
    ExpressionNode& rightExpr;
    int op;
    
    BinaryOperatorNode(ExpressionNode& left, int& op, ExpressionNode& right):
        leftExpr(left), op(op), rightExpr(right){}
    
    ValuePtr generateCode(CodeGenerationContext& context);
};


class MethodCallNode: public ExpressionNode{
public:
    const IdentifierNode& id;
    ExpressionList args;

    MethodCallNode(const IdentifierNode& id): id(id){}
    MethodCallNode(const IdentifierNode& id, ExpressionList& args):id(id), args(args){}

    ValuePtr generateCode(CodeGenerationContext& context);
};

class AssignmentNode: public ExpressionNode{
public:
    IdentifierNode& id;
    ExpressionNode& expr;

    AssignmentNode(IdentifierNode& id, ExpressionNode& expr):id(id), expr(expr){}

    ValuePtr generateCode(CodeGenerationContext& context);
};

class BlockNode: public StatementNode{
public:
    StatementList statements;
    BlockNode(){}

    ValuePtr generateCode(CodeGenerationContext& context);
};

class ExpressionStatementNode: public StatementNode{
public:
    ExpressionNode& expr;
    ExpressionStatementNode(ExpressionNode& expr): expr(expr){}

    ValuePtr generateCode(CodeGenerationContext& context);
};

class FunctionDeclarationNode: public StatementNode{
public:
    const IdentifierNode& type;
    const IdentifierNode& id;
    VariableList args;
    BlockNode& block;

    FunctionDeclarationNode(const IdentifierNode& type, const IdentifierNode& id,
                            const VariableList& args, BlockNode& block):
                            type(type),id(id),args(args),block(block){}

    ValuePtr generateCode(CodeGenerationContext& context);
};

class VariableDeclarationNode: public StatementNode{
public:
    const IdentifierNode& type;
    IdentifierNode& id;
    std::shared_ptr<ExpressionNode> assignmentExpr;

    VariableDeclarationNode(const IdentifierNode& type, IdentifierNode& id):
        type(type), id(id), assignmentExpr(nullptr) {}

    VariableDeclarationNode(const IdentifierNode& type, IdentifierNode& id,
                            std::shared_ptr<ExpressionNode>& expr):
                            type(type), id(id), assignmentExpr(expr){}
    

    ValuePtr generateCode(CodeGenerationContext& context);
};