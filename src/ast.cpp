#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Verifier.h"
#include <string>
#include <functional>

#include "ast.h"
#include "context.h"

int debug_on = 1;

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

static LLVMContext AnLLVMContextInstance;
static IRBuilder<> builderapi(AnLLVMContextInstance);
static TypeSystem typesys(AnLLVMContextInstance);

ValuePtr BinaryOperatorNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr opL = leftExpr->generateCode(context);
    ValuePtr opR = rightExpr->generateCode(context);
    
    if(!opL || !opR)
        Log::raiseError("Invalid Oprands near operator with code [" + std::to_string(this->op) + "]!", std::cout);

    auto typeL = opL->getType()->getTypeID();
    auto typeR = opR->getType()->getTypeID();
    bool LisDouble = 0, RisDouble = 0;
    if(typeL == Type::DoubleTyID)
        LisDouble = 1;
    if(typeR == Type::DoubleTyID)
        RisDouble = 1;

    switch(this->op)
    {
        case yytokentype::LT:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateICmpSLT(opL, opR, "Icmp");
            else
                return builderapi.CreateFCmpULT(opL, opR, "Dcmp");
        case yytokentype::GT:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateICmpSGT(opL, opR, "Icmp");
            else
                return builderapi.CreateFCmpUGT(opL, opR, "Dcmp");
        case yytokentype::LE:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateICmpSLE(opL, opR, "Icmp");
            else
                return builderapi.CreateFCmpULE(opL, opR, "Dcmp");
        case yytokentype::GE:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateICmpSGE(opL, opR, "Icmp");
            else
                return builderapi.CreateFCmpUGE(opL, opR, "Dcmp");
        case yytokentype::EQUAL:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateICmpEQ(opL, opR, "Icmp");
            else
                return builderapi.CreateFCmpUEQ(opL, opR, "Dcmp");
        case yytokentype::NEQUAL:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateICmpNE(opL, opR, "Icmp");
            else
                return builderapi.CreateFCmpUNE(opL, opR, "Dcmp");

        case yytokentype::PLUS:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateAdd(opL, opR, "Iaddtmp");
            else
                return builderapi.CreateFAdd(opL, opR, "Daddtmp");

        case yytokentype::MINUS:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateSub(opL, opR, "Isubtmp");
            else
                return builderapi.CreateFSub(opL, opR, "Dsubtmp");

        case yytokentype::MUL:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateMul(opL, opR, "Imultmp");
            else
                return builderapi.CreateFMul(opL, opR, "Dmultmp");

        case yytokentype::DIV:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateSDiv(opL, opR, "Idivtmp");
            else
                return builderapi.CreateFDiv(opL, opR, "Ddivtmp");

        case yytokentype::AND:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateAnd(opL, opR, "andtmp");
            else
            {
                Log::raiseError("Invalid bit operation operand!", std::cout);
                break;
            }

        case yytokentype::OR:
            if(!LisDouble && !RisDouble)
                return builderapi.CreateAnd(opL, opR, "andtmp");
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
    for(auto it = this->statements.begin(); it != this->statements.end(); ++it)
        (*it)->generateCode(context);
    return nullptr;
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
    Type * retTp = typesys.getLlvmVarType(*(this->type));
    
    
    
    
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
    if(program != nullptr){
    if(dbg_on) program->debugPrint("");
    llvm::LLVMContext llvmctxt;
    CodeGenerationContext ctxt;
    program->generateCode(ctxt);
    delete program;
}