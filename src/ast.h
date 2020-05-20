#pragma once

#include<iostream>
#include<vector>
#include<string>
//#include<llvm/IR/Value.h>
#include<memory>


class ExpressionNode;
class VariableDeclarationNode;
class StatementNode;
//class CodeGenerationContext;

//typedef llvm::Value* ValuePtr;
typedef std::vector<std::shared_ptr<ExpressionNode>> ExpressionList;
typedef std::vector<std::shared_ptr<StatementNode>> StatementList;
typedef std::vector<std::shared_ptr<VariableDeclarationNode>> VariableList;

using std::shared_ptr;
using std::make_shared;

class ASTNode{
public:
    virtual ~ASTNode(){}
    // virtual ValuePtr generateCode(CodeGenerationContext& context){
    //     return nullptr;
    // }

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
    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"IntegerNode( value: "<<value<<")\n";
    }
};

class CharNode: public ExpressionNode{
public:
    char value;
    CharNode(const char& value): value(value){}
    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"CharNode( value: "<<value<<")\n";
    }
};

class RealNode: public ExpressionNode{
public:
    double value;
    RealNode(const double& value): value(value){}
    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"RealNode( value: "<<value<<")\n";
    }
};

class BoolNode: public ExpressionNode{
public:
    bool value;
    BoolNode(const bool& value): value(value){}

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"BoolNode( value: "<<value<<")\n";
    }
};


class IdentifierNode: public ExpressionNode{
public:
    std::string name;
    bool isType = false;
    bool isArray = false;

    shared_ptr<ExpressionList> arraySize = nullptr;

    IdentifierNode(const std::string& name): name(name){}

    IdentifierNode(const std::string& name, ExpressionList*& size):
                name(name){
                    arraySize = shared_ptr<ExpressionList>(size);
                }

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"IdentifierNode( name: "
                        <<name<<", isType: "<<isType
                        <<", isArray: "<<isArray<<")\n";
    }
};

class BinaryOperatorNode: public ExpressionNode{
public:
    shared_ptr<ExpressionNode> leftExpr;
    shared_ptr<ExpressionNode> rightExpr;
    int op;
    
    BinaryOperatorNode(ExpressionNode*& left, int& op, ExpressionNode*& right):
        op(op){
            leftExpr = shared_ptr<ExpressionNode>(left);
            rightExpr = shared_ptr<ExpressionNode>(right);
        }
    
    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"BinaryOperatorNode( op: "<<op<<")\n";
        std::cout<<prefix<<"\tLeftExpr:\n";
        leftExpr->debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\tRightExpr:\n";
        rightExpr->debugPrint(prefix + "\t\t");
    }
};


class MethodCallNode: public ExpressionNode{
public:
    const shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionList> args;

    MethodCallNode(IdentifierNode*& id): id(shared_ptr<IdentifierNode>(id)), args(nullptr){}
    MethodCallNode(IdentifierNode*& id, ExpressionList*& args):id(shared_ptr<IdentifierNode>(id)), 
                    args(shared_ptr<ExpressionList>(args)){}

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"MethodCallNode\n";
        std::cout<<prefix<<"\tid:\n";
        id->debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\targs:\n";
        for(auto& expr: *args){
            expr->debugPrint(prefix + "\t\t");
        }
    }
};

class AssignmentNode: public ExpressionNode{
public:
    shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionNode> expr;

    AssignmentNode(IdentifierNode*& id, ExpressionNode*& expr){
        this->id = shared_ptr<IdentifierNode>(id);
        this->expr = shared_ptr<ExpressionNode>(expr);
    }

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"AssignmentNode\n";
        std::cout<<prefix<<"\tid:\n";
        id->debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\texpr:\n";
        expr->debugPrint(prefix + "\t\t");
    }

};


class ArrayIndexNode:public ExpressionNode{
public:
    shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionNode> index;

    ArrayIndexNode(IdentifierNode*& id, ExpressionNode*& index)
                    {
                        this->id = shared_ptr<IdentifierNode>(id);
                        this->index = shared_ptr<ExpressionNode>(index);
                    }

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"AssignmentNode\n";
        std::cout<<prefix<<"\tid:\n";
        id->debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\tindex:\n";
        index->debugPrint(prefix + "\t\t");
    }
};



class BlockNode: public StatementNode{
public:
    StatementList statements;
    BlockNode(){}

    //ValuePtr generateCode(CodeGenerationContext& context);

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
    shared_ptr<ExpressionNode> expr;
    ExpressionStatementNode(ExpressionNode*& expr){
        this->expr = shared_ptr<ExpressionNode>(expr);
    }

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"ExpressionStatementNode\n";
        std::cout<<prefix<<"\texpr:\n";
        expr->debugPrint(prefix + "\t\t");
    }

};

class FunctionDeclarationNode: public StatementNode{
public:
    shared_ptr<IdentifierNode> type;
    shared_ptr<IdentifierNode> id;
    shared_ptr<VariableList> args;
    shared_ptr<BlockNode> block;

    FunctionDeclarationNode(IdentifierNode*& type, IdentifierNode*& id,
                            VariableList*& args, BlockNode*& block):
                            type(shared_ptr<IdentifierNode>(type)),
                            id(shared_ptr<IdentifierNode>(id)),
                            args(shared_ptr<VariableList>(args)),
                            block(shared_ptr<BlockNode>(block)){
                            }

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"FunctionDeclarationNode\n";
        
        std::cout<<prefix<<"\ttype:\n";
        if(type){
            type->debugPrint(prefix + "\t\t");
        }else{
            std::cout<<prefix<<"\t\tVoid\n";
        }

        std::cout<<prefix<<"\tid:\n";
        id->debugPrint(prefix + "\t\t");
        
        std::cout<<prefix<<"\targs:\n";
        for(auto& arg: *args){
            arg->debugPrint(prefix + "\t\t");
        }

        std::cout<<prefix<<"\tblock:\n";
        block->debugPrint(prefix + "\t\t");
    }

};

class VariableDeclarationNode: public StatementNode{
public:
    const shared_ptr<IdentifierNode> type;
    shared_ptr<IdentifierNode> id;
    shared_ptr<ExpressionNode> assignmentExpr; //Nullable

    VariableDeclarationNode(IdentifierNode*& type, IdentifierNode*& id):
        type(shared_ptr<IdentifierNode>(type)), 
        id(shared_ptr<IdentifierNode>(id)), 
        assignmentExpr(nullptr) {}

    VariableDeclarationNode(IdentifierNode*& type, IdentifierNode*& id,
                            ExpressionNode*& expr):
                            type(shared_ptr<IdentifierNode>(type)), 
                            id(shared_ptr<IdentifierNode>(id)), 
                            assignmentExpr(shared_ptr<ExpressionNode>(expr)){}
    

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"VariableDeclarationNode\n";
        std::cout<<prefix<<"\ttype:\n";
        type->debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\tid:\n";
        id->debugPrint(prefix + "\t\t");
        if(assignmentExpr){
            std::cout<<prefix<<"\texpr:\n";
            assignmentExpr->debugPrint(prefix + "\t\t");
        }
    }
};


class IfStatementNode: public StatementNode{
public:
    shared_ptr<ExpressionNode> condition;
    shared_ptr<BlockNode> trueBlock;
    shared_ptr<BlockNode> falseBlock;

    IfStatementNode(ExpressionNode*& condition, BlockNode*& trueBlock, BlockNode*& falseBlock):
            condition(shared_ptr<ExpressionNode>(condition)),
            trueBlock(shared_ptr<BlockNode>(trueBlock)),
            falseBlock(shared_ptr<BlockNode>(falseBlock)){}

    //ValuePtr generateCode(CodeGenerationContext& context);

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"IfStatementNode\n";
        std::cout<<prefix<<"\tcondition:\n";
        condition->debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\ttrueBlock:\n";
        trueBlock->debugPrint(prefix + "\t\t");
        if(falseBlock){
            std::cout<<prefix<<"\tfalseBlock:\n";
            falseBlock->debugPrint(prefix + "\t\t");
        }
    }

};


class WhileStatementNode: public StatementNode{
public:
    shared_ptr<ExpressionNode> condition;
    shared_ptr<BlockNode> block;

    WhileStatementNode(ExpressionNode*& condition, BlockNode*& block):
            condition(shared_ptr<ExpressionNode>(condition)),
            block(shared_ptr<BlockNode>(block)){}

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"WhileStatementNode\n";
        std::cout<<prefix<<"\tcondition:\n";
        condition->debugPrint(prefix + "\t\t");
        std::cout<<prefix<<"\tBlock:\n";
        block->debugPrint(prefix + "\t\t");
    }

};

class ReturnStatementNode: public StatementNode{
public:
    shared_ptr<ExpressionNode> expr;

    ReturnStatementNode(ExpressionNode*& expr): expr(shared_ptr<ExpressionNode>(expr)){}

    void debugPrint(std::string prefix) const{
        std::cout<<prefix<<"ReturnStatementNode\n";
        std::cout<<prefix<<"\texpr:\n";
        if(expr){
            expr->debugPrint(prefix + "\t\t");
        }else{
            std::cout<<prefix<<"\t\tNull\n";
        }
        
    }

};

