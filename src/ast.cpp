#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"

#include "llvm/IR/BasicBlock.h"
#include <llvm/IR/Constants.h>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Verifier.h"
#include <string>
#include <functional>

#include "ast.h"
#include "context.h"



ValuePtr IntegerNode::generateCode(CodeGenerationContext& context) const {
    Type* type = Type::getInt32Ty(context.llvmContext); //设置返回值的类型为int32
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr CharNode::generateCode(CodeGenerationContext &context) const {
    Type* type = Type::getInt16Ty(context.llvmContext);
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr RealNode::generateCode(CodeGenerationContext &context) const {
    Type* type = Type::getDoubleTy(context.llvmContext);
    return llvm::ConstantFP::get(type, value);
}

ValuePtr BoolNode::generateCode(CodeGenerationContext &context) const {
    Type* type = Type::getInt1Ty(context.llvmContext);
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr IdentifierNode::generateCode(CodeGenerationContext &context) const {
    //this-

    return nullptr;
}


ValuePtr BinaryOperatorNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr opL = leftExpr->generateCode(context);
    ValuePtr opR = rightExpr->generateCode(context);
    
    if(!opL || !opR) {
        Log::raiseError("Invalid Oprands near operator with code [" + std::to_string(this->op) + "]!", std::cout);
        return nullptr;
    }


    auto typeL = opL->getType()->getTypeID();
    auto typeR = opR->getType()->getTypeID();
    bool bothFloat = false;

    if(typeL == Type::DoubleTyID || typeR == Type::DoubleTyID){
        bothFloat = true;
        if(!(typeL == Type::DoubleTyID)){
            opL = context.builder.CreateSIToFP(opL, Type::getDoubleTy(context.llvmContext), "fopL");
        }

        if (!(typeR == Type::DoubleTyID)){
            opR = context.builder.CreateSIToFP(opL, Type::getDoubleTy(context.llvmContext), "fopR");
        }
    }


    switch(this->op)
    {
        case yytokentype::LT:
            if(!bothFloat)
                return context.builder.CreateICmpSLT(opL, opR, "Ilt");
            else
                return context.builder.CreateFCmpULT(opL, opR, "Dlt");
        case yytokentype::GT:
            if(!bothFloat)
                return context.builder.CreateICmpSGT(opL, opR, "Igt");
            else
                return context.builder.CreateFCmpUGT(opL, opR, "Dgt");
        case yytokentype::LE:
            if(!bothFloat)
                return context.builder.CreateICmpSLE(opL, opR, "Ile");
            else
                return context.builder.CreateFCmpULE(opL, opR, "Dle");
        case yytokentype::GE:
            if(!bothFloat)
                return context.builder.CreateICmpSGE(opL, opR, "Ige");
            else
                return context.builder.CreateFCmpUGE(opL, opR, "Dge");
        case yytokentype::EQUAL:
            if(!bothFloat)
                return context.builder.CreateICmpEQ(opL, opR, "Ieq");
            else
                return context.builder.CreateFCmpUEQ(opL, opR, "Deq");
        case yytokentype::NEQUAL:
            if(!bothFloat)
                return context.builder.CreateICmpNE(opL, opR, "Ine");
            else
                return context.builder.CreateFCmpUNE(opL, opR, "Dne");

        case yytokentype::PLUS:
            if(!bothFloat)
                return context.builder.CreateAdd(opL, opR, "Iaddtmp");
            else
                return context.builder.CreateFAdd(opL, opR, "Daddtmp");

        case yytokentype::MINUS:
            if(!bothFloat)
                return context.builder.CreateSub(opL, opR, "Isubtmp");
            else
                return context.builder.CreateFSub(opL, opR, "Dsubtmp");

        case yytokentype::MUL:
            if(!bothFloat)
                return context.builder.CreateMul(opL, opR, "Imultmp");
            else
                return context.builder.CreateFMul(opL, opR, "Dmultmp");

        case yytokentype::DIV:
            if(!bothFloat)
                return context.builder.CreateSDiv(opL, opR, "Idivtmp");
            else
                return context.builder.CreateFDiv(opL, opR, "Ddivtmp");

        case yytokentype::AND:
            if(!bothFloat) {
                return context.builder.CreateAnd(opL, opR, "andtmp");
            }else
            {
                Log::raiseError("Invalid bit operation operand!", std::cout);
                break;
            }

        case yytokentype::OR:
            if(!bothFloat) {
                return context.builder.CreateAnd(opL, opR, "andtmp");
            }
            else
            {
                Log::raiseError("Invalid bit operation operand!", std::cout);
                break;
            }

        default:
            Log::raiseError("Undefined Operator!", std::cout);

    } 

    return nullptr;
}

ValuePtr FunctionCallNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr AssignmentNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr ArrayIndexNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr ArrayIndexAssignmentNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    
    return nullptr;
}

ValuePtr BlockNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr value = nullptr;

    for(auto it = this->statements.begin(); it != this->statements.end(); ++it)
        value = (*it)->generateCode(context);
    return value;
}

ValuePtr VariableDeclarationNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr ExpressionStatementNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr FunctionDeclarationNode::generateCode(CodeGenerationContext &context) const {
    Type * retTp = context.typeSystem.getLLVMVarType(*(this->type));
    
    
    
    
    return nullptr;
}

ValuePtr IfStatementNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr WhileStatementNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr ReturnStatementNode::generateCode(CodeGenerationContext &context) const {
    if(expr){
        ValuePtr value = expr->generateCode(context);
        context.setCurrentReturnValue(value);
        return value;
    }else{
        return nullptr;
    }
}

void compile_and_run(BlockNode *program)
{
    if(program != nullptr) {
        program->debugPrint("");
//        CodeGenerationContext ctxt;
//        program->generateCode(ctxt);
        delete program;
    }
}