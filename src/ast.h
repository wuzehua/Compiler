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

    virtual void debugPrint(std::string prefix) const{}

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

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"IntegerNode( value: "<<value<<")\n";
    }
};

class CharNode: public ExpressionNode{
public:
    char value;
    CharNode(const char& value): value(value){}
    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"CharNode( value: "<<value<<")\n";
    }
};

class RealNode: public ExpressionNode{
public:
    double value;
    RealNode(const double& value): value(value){}
    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"RealNode( value: "<<value<<")\n";
    }
};


class IdentifierNode: public ExpressionNode{
public:
    std::string name;
    bool isType = false;
    bool isArray = false;

    std::shared_ptr<ExpressionList> arraySize = nullptr;

    IdentifierNode(const std::string& name): name(name){}

    IdentifierNode(const std::string& name, std::shared_ptr<ExpressionList>& size):
                name(name), arraySize(size){}

    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"IdentifierNode( name: "
                        <<name<<", isType: "<<isType
                        <<", isArray: "<<isArray<<")\n";
    }
};

class BinaryOperatorNode: public ExpressionNode{
public:
    ExpressionNode& leftExpr;
    ExpressionNode& rightExpr;
    int op;
    
    BinaryOperatorNode(ExpressionNode& left, int& op, ExpressionNode& right):
        leftExpr(left), op(op), rightExpr(right){}
    
    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"BinaryOperatorNode( op: "<<op<<")\n";
        std::cout<<prefix<<"\tLeftExpr:\n";
        leftExpr.debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\tRightExpr:\n";
        rightExpr.debugPrint(prefix + "\t\t");
    }
};


class MethodCallNode: public ExpressionNode{
public:
    const IdentifierNode& id;
    ExpressionList args;

    MethodCallNode(const IdentifierNode& id): id(id){}
    MethodCallNode(const IdentifierNode& id, ExpressionList& args):id(id), args(args){}

    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"MethodCallNode\n";
        std::cout<<prefix<<"\tid:\n";
        id.debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\targs:\n";
        for(auto& expr: args){
            expr->debugPrint(prefix + "\t\t");
        }
    }
};

class AssignmentNode: public ExpressionNode{
public:
    IdentifierNode& id;
    ExpressionNode& expr;

    AssignmentNode(IdentifierNode& id, ExpressionNode& expr):id(id), expr(expr){}

    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"AssignmentNode\n";
        std::cout<<prefix<<"\tid:\n";
        id.debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\texpr:\n";
        expr.debugPrint(prefix + "\t\t");
    }

};

class BlockNode: public StatementNode{
public:
    StatementList statements;
    BlockNode(){}

    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"BlockNode\n";
        std::cout<<prefix<<"\tstatements:\n";
        for(auto& stat: statements){
            stat->debugPrint(prefix + "\t\t");
        }
    }
};

class ExpressionStatementNode: public StatementNode{
public:
    ExpressionNode& expr;
    ExpressionStatementNode(ExpressionNode& expr): expr(expr){}

    ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"ExpressionStatementNode\n";
        std::cout<<prefix<<"\texpr:\n";
        expr.debugPrint(prefix + "\t\t");
    }

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

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"FunctionDeclarationNode\n";
        
        std::cout<<prefix<<"\ttype:\n";
        type.debugPrint(prefix + "\t\t");
        
        std::cout<<prefix<<"\tid:\n";
        id.debugPrint(prefix + "\t\t");
        
        std::cout<<prefix<<"\targs:\n";
        for(auto& arg: args){
            arg->debugPrint(prefix + "\t\t");
        }

        std::cout<<prefix<<"\tblock:\n";
        block.debugPrint(prefix + "\t\t");
    }

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

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"VariableDeclarationNode\n";
        std::cout<<prefix<<"\ttype:\n";
        type.debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\tid:\n";
        id.debugPrint(prefix + "\t\t");
        if(assignmentExpr){
            std::cout<<prefix<<"\texpr:\n";
            assignmentExpr->debugPrint(prefix + "\t\t");
        }
    }
};