#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>

#include "ast.h"
#include "context.h"

ValuePtr IntegerNode::generateCode(CodeGenerationContext& context) const {
    Type* type = Type::getInt64Ty(context.llvmContext); //设置返回值的类型为int64
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
    //TODO
    return nullptr;
}


ValuePtr BinaryOperatorNode::generateCode(CodeGenerationContext &context) const {
    //TODO
    return nullptr;
}

ValuePtr MethodCallNode::generateCode(CodeGenerationContext &context) const {
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
    //TODO
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
    //TODO
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