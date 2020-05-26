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
    ValuePtr var = context.getSymbolValue(this->id->name);
    TypePtr varTp = context.typeSystem.getLLVMVarType(context.getSymbolType(this->id->name)->name);

    

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
    BasicBlock* basicBlock = BasicBlock::Create(context.llvmContext, "codeBlock");
    context.pushCodeBlock(basicBlock);
    for(auto it = this->statements.begin(); it != this->statements.end(); ++it)
        value = (*it)->generateCode(context);
    context.popCurrentCodeBlock();
    return value;
}

ValuePtr VariableDeclarationNode::generateCode(CodeGenerationContext &context) const {
    
    TypePtr type = context.typeSystem.getLLVMVarType(this->type->name);
    ValuePtr val = nullptr;
    Value *cd;
    if(!(this->type->isArray))
    {
        cd = context.builder.CreateAlloca(type);
    }
    //TODO: Add support for array
    /*else
    {
        int len = this->id->arraySize;
        std::vector<unsigned long long> arrayDimensions;
        

        cd = context.builder.CreateAlloca()
    }*/
    

    return cd;
}

ValuePtr ExpressionStatementNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr FunctionDeclarationNode::generateCode(CodeGenerationContext &context) const {
    Type * retTp = context.typeSystem.getLLVMType(type);
    
    std::vector<TypePtr> argsTypeVec;

    for(auto & it : *this->args)
        argsTypeVec.emplace_back(context.typeSystem.getLLVMVarType(it->type->name));

    FunctionType *thisFuncType = FunctionType::get(retTp, argsTypeVec, false);

    Function *thisFunc = Function::Create(
        thisFuncType, Function::ExternalLinkage, this->id->name, context.theModule.get());

    BasicBlock* funcBlock = BasicBlock::Create(context.llvmContext, "entry", thisFunc);
    context.builder.SetInsertPoint(funcBlock);
    context.pushCodeBlock(funcBlock);

    auto args_it = this->args->begin();
    auto llvmargs_it = thisFunc->args().begin();
    for(; args_it != this->args->end() && llvmargs_it != thisFunc->args().end(); 
        ++args_it, ++llvmargs_it)
    {
        llvmargs_it->setName((*args_it)->id->name);
        ValuePtr val;
        if((*args_it)->type->isArray)
            val = context.builder.CreateAlloca(context.typeSystem.getLLVMVarType((*args_it)->type->name), 0U);
        else
            val = (*args_it)->generateCode(context);
        context.builder.CreateStore(llvmargs_it, val, false);
        context.createSymbol((*args_it)->id->name);
        context.setFuncArg((*args_it)->id->name, true);
        context.setSymbolValue((*args_it)->id->name, val);
        context.setSymbolType((*args_it)->id->name, (*args_it)->type);
    }
    //TODO: Not complete

    return thisFunc;
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
