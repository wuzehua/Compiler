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

#define ISTYPE(value, id) (value->getType()->getTypeID() == id)


ValuePtr IntegerNode::generateCode(CodeGenerationContext &context) const {
    Type *type = Type::getInt32Ty(context.llvmContext); //设置返回值的类型为int32
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr CharNode::generateCode(CodeGenerationContext &context) const {
    Type *type = Type::getInt16Ty(context.llvmContext);
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr RealNode::generateCode(CodeGenerationContext &context) const {
    Type *type = Type::getDoubleTy(context.llvmContext);
    return llvm::ConstantFP::get(type, value);
}

ValuePtr BoolNode::generateCode(CodeGenerationContext &context) const {
    Type *type = Type::getInt1Ty(context.llvmContext);
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr IdentifierNode::generateCode(CodeGenerationContext &context) const {
    Value *value = context.getSymbolValue(name);
    if (!value) {
        Log::raiseError("Unknown variable name " + this->name, std::cout);
        return nullptr;
    }
    if (value->getType()->isPointerTy()) {
        auto valuePtr = context.builder.CreateLoad(value, "valuePtr");
        if (valuePtr->getType()->isArrayTy()) {
            std::vector<Value *> index;
            index.push_back(ConstantInt::get(Type::getInt32PtrTy(context.llvmContext), 0, false));
            auto ptr = context.builder.CreateInBoundsGEP(value, index, "valuePtr");
            return ptr;
        }
    }
    return context.builder.CreateLoad(value, false, "");
}


ValuePtr BinaryOperatorNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr opL = leftExpr->generateCode(context);
    ValuePtr opR = rightExpr->generateCode(context);

    if (!opL || !opR) {
        Log::raiseError("Invalid Oprands near operator with code [" + std::to_string(this->op) + "]!", std::cout);
        return nullptr;
    }


    auto typeL = opL->getType()->getTypeID();
    auto typeR = opR->getType()->getTypeID();
    bool bothFloat = false;

    if (typeL == Type::DoubleTyID || typeR == Type::DoubleTyID) {
        bothFloat = true;
        if (!(typeL == Type::DoubleTyID)) {
            opL = context.builder.CreateSIToFP(opL, Type::getDoubleTy(context.llvmContext), "fopL");
        }

        if (!(typeR == Type::DoubleTyID)) {
            opR = context.builder.CreateSIToFP(opL, Type::getDoubleTy(context.llvmContext), "fopR");
        }
    }


    switch (this->op) {
        case yytokentype::LT:
            if (!bothFloat)
                return context.builder.CreateICmpSLT(opL, opR, "Ilt");
            else
                return context.builder.CreateFCmpULT(opL, opR, "Dlt");
        case yytokentype::GT:
            if (!bothFloat)
                return context.builder.CreateICmpSGT(opL, opR, "Igt");
            else
                return context.builder.CreateFCmpUGT(opL, opR, "Dgt");
        case yytokentype::LE:
            if (!bothFloat)
                return context.builder.CreateICmpSLE(opL, opR, "Ile");
            else
                return context.builder.CreateFCmpULE(opL, opR, "Dle");
        case yytokentype::GE:
            if (!bothFloat)
                return context.builder.CreateICmpSGE(opL, opR, "Ige");
            else
                return context.builder.CreateFCmpUGE(opL, opR, "Dge");
        case yytokentype::EQUAL:
            if (!bothFloat)
                return context.builder.CreateICmpEQ(opL, opR, "Ieq");
            else
                return context.builder.CreateFCmpUEQ(opL, opR, "Deq");
        case yytokentype::NEQUAL:
            if (!bothFloat)
                return context.builder.CreateICmpNE(opL, opR, "Ine");
            else
                return context.builder.CreateFCmpUNE(opL, opR, "Dne");

        case yytokentype::PLUS:
            if (!bothFloat)
                return context.builder.CreateAdd(opL, opR, "Iaddtmp");
            else
                return context.builder.CreateFAdd(opL, opR, "Daddtmp");

        case yytokentype::MINUS:
            if (!bothFloat)
                return context.builder.CreateSub(opL, opR, "Isubtmp");
            else
                return context.builder.CreateFSub(opL, opR, "Dsubtmp");

        case yytokentype::MUL:
            if (!bothFloat)
                return context.builder.CreateMul(opL, opR, "Imultmp");
            else
                return context.builder.CreateFMul(opL, opR, "Dmultmp");

        case yytokentype::DIV:
            if (!bothFloat)
                return context.builder.CreateSDiv(opL, opR, "Idivtmp");
            else
                return context.builder.CreateFDiv(opL, opR, "Ddivtmp");

        case yytokentype::AND:
            if (!bothFloat) {
                return context.builder.CreateAnd(opL, opR, "andtmp");
            } else {
                Log::raiseError("Invalid bit operation operand!", std::cout);
                break;
            }

        case yytokentype::OR:
            if (!bothFloat) {
                return context.builder.CreateAnd(opL, opR, "andtmp");
            } else {
                Log::raiseError("Invalid bit operation operand!", std::cout);
                break;
            }

        default:
            Log::raiseError("Undefined Operator!", std::cout);
    }

    return nullptr;
}

ValuePtr FunctionCallNode::generateCode(CodeGenerationContext &context) const {
    Function *calleeF = context.theModule->getFunction(id->name);
    if (!calleeF) {
        Log::raiseError("Function not found", std::cout);
    }
    if (calleeF->arg_size() != args->size()) {
        Log::raiseError("Function args number not match, " + id->name + " requires " + std::to_string(calleeF->size()) +
                        "args, but " + std::to_string(args->size()) + "args are given", std::cout);
    }
    std::vector<Value *> argsList;
    for (auto it = args->begin(); it != args->end(); it++) {
        argsList.push_back((*it)->generateCode(context));
        if (!argsList.back()) {        // if any arg codegen fail
            return nullptr;
        }
    }
    return context.builder.CreateCall(calleeF, argsList, "calltmp");
}

ValuePtr AssignmentNode::generateCode(CodeGenerationContext &context) const {
    auto var = context.getSymbolValue(id->name);
    if (!var) {
        Log::raiseError("Undefined variable", std::cout);
        return nullptr;
    }
    ValuePtr exp = expr->generateCode(context);
    exp = context.typeSystem.cast(exp, context.typeSystem.getLLVMVarType(context.getSymbolType(id->name)->name),
                                  context.getCurrentBasicBlock());
    context.builder.CreateStore(exp, var);
    return var;
}

ValuePtr ArrayIndexNode::generateCode(CodeGenerationContext &context) const {
    auto var = context.getSymbolValue(id->name);
    auto type = context.getSymbolType(id->name);

    if (!var) {
        Log::raiseError("Undefined variable", std::cout);
        return nullptr;
    }

    if (!type->isArray) {
        Log::raiseError(id->name + "is not an array", std::cout);
        return nullptr;
    }

    auto value = index->generateCode(context);
    ArrayRef<ValuePtr> indices;
    if (context.isFuncArg(id->name)) {
        var = context.builder.CreateLoad(var, "arrayPtr");
        //TODO fix assignment bug
//        indices = {value};
    } else if (var->getType()->isPointerTy()) {
        indices = {ConstantInt::get(Type::getInt64Ty(context.llvmContext), 0), value};
    } else {
        Log::raiseError(id->name + "is not an array", std::cout);
        return nullptr;
    }

    return context.builder.CreateAlignedLoad(context.builder.CreateInBoundsGEP(var, indices, "elementPtr"), 4);
}

ValuePtr ArrayIndexAssignmentNode::generateCode(CodeGenerationContext &context) const {
    auto var = context.getSymbolValue(element->id->name);

    if (!var) {
        Log::raiseError("Undefined variable", std::cout);
        return nullptr;
    }

    auto arrVar = context.builder.CreateLoad(var, "arrayPtr");

    if (!arrVar->getType()->isArrayTy() && !arrVar->getType()->isPointerTy()) {
        Log::raiseError(element->id->name + "is not an array", std::cout);
        return nullptr;
    }

    auto index = element->index->generateCode(context);
    ArrayRef<ValuePtr> indices = {ConstantInt::get(Type::getInt64Ty(context.llvmContext), 0), index};

    return context.builder.CreateAlignedStore(expr->generateCode(context),
                                              context.builder.CreateInBoundsGEP(var, indices, "elementPtr"), 4);
}

ValuePtr BlockNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr value = nullptr;
    BasicBlock *basicBlock = BasicBlock::Create(context.llvmContext, "codeBlock");
    context.pushCodeBlock(basicBlock);
    for (auto it = this->statements.begin(); it != this->statements.end(); ++it)
        value = (*it)->generateCode(context);
    context.popCurrentCodeBlock();
    return value;
}

ValuePtr VariableDeclarationNode::generateCode(CodeGenerationContext &context) const {

    TypePtr typePtr = context.typeSystem.getLLVMVarType(type->name);
    ValuePtr val = nullptr;
    ValuePtr cd;
    if (type->isArray) {
        uint64_t arraySize = 1;
        std::vector<uint64_t> arraySizes;
        auto *integer = dynamic_cast<IntegerNode *>(type->arraySize.get());
        arraySize *= integer->value;
        arraySizes.push_back(integer->value);

        context.setArraySize(id->name, arraySizes);
        Value *arraySizeValue = IntegerNode(arraySize).generateCode(context);
        auto arrayType = ArrayType::get(context.typeSystem.getLLVMVarType(type->name), arraySize);
        cd = context.builder.CreateAlloca(arrayType, arraySizeValue, "arraytmp");

    } else {
        cd = context.builder.CreateAlloca(typePtr);
    }

    context.setSymbolType(id->name, type);
    context.setSymbolValue(id->name, cd);

    context.PrintSymTable();

    if (assignmentExpr) {
        AssignmentNode assignment(id, assignmentExpr);
        assignment.generateCode(context);
    }

    return cd;
}

ValuePtr ExpressionStatementNode::generateCode(CodeGenerationContext &context) const {
    return expr->generateCode(context);
}

ValuePtr FunctionDeclarationNode::generateCode(CodeGenerationContext &context) const {
    Type *retTp = context.typeSystem.getLLVMType(type);

    std::vector<TypePtr> argsTypeVec;

    for (auto &it : *this->args)
        argsTypeVec.emplace_back(context.typeSystem.getLLVMVarType(it->type->name));

    FunctionType *thisFuncType = FunctionType::get(retTp, argsTypeVec, false);

    Function *thisFunc = Function::Create(thisFuncType, Function::ExternalLinkage, this->id->name,
                                          context.theModule.get());

    BasicBlock *funcBlock = BasicBlock::Create(context.llvmContext, "entry", thisFunc);
    context.builder.SetInsertPoint(funcBlock);
    context.pushCodeBlock(funcBlock);

    auto args_it = this->args->begin();
    auto llvmargs_it = thisFunc->args().begin();
    for (; args_it != this->args->end() && llvmargs_it != thisFunc->args().end(); ++args_it, ++llvmargs_it) {
        llvmargs_it->setName((*args_it)->id->name);
        ValuePtr val;
        if ((*args_it)->type->isArray)
            val = context.builder.CreateAlloca(context.typeSystem.getLLVMVarType((*args_it)->type->name), 0U);
        else
            val = (*args_it)->generateCode(context);
        context.builder.CreateStore(llvmargs_it, val, false);
        context.createSymbol((*args_it)->id->name);
        context.setFuncArg((*args_it)->id->name, true);
        context.setSymbolValue((*args_it)->id->name, val);
        context.setSymbolType((*args_it)->id->name, (*args_it)->type);
    }

    block->generateCode(context);
    if (context.getCurrentReturnValue()) {
        context.builder.CreateRet(context.getCurrentReturnValue());
    } else {
        Log::raiseError("Function block return value not founded", std::cout);
        return nullptr;
    }

    context.popCurrentCodeBlock();

    return thisFunc;
}

static ValuePtr CastToBoolean(CodeGenerationContext &context, ValuePtr value) {

    if (ISTYPE(value, Type::IntegerTyID)) {
        value = context.builder.CreateIntCast(value, Type::getInt1Ty(context.llvmContext), true);
        return context.builder.CreateICmpNE(value, ConstantInt::get(Type::getInt1Ty(context.llvmContext), 0, true));
    } else if (ISTYPE(value, Type::DoubleTyID)) {
        return context.builder.CreateFCmpONE(value, ConstantFP::get(context.llvmContext, APFloat(0.0)));
    } else {
        return value;
    }
}

ValuePtr IfStatementNode::generateCode(CodeGenerationContext &context) const {
    Value *cond = condition->generateCode(context);
    if (!cond)
        return nullptr;

    cond = CastToBoolean(context, cond);

    Function *theFunction = context.builder.GetInsertBlock()->getParent();      // the function where if statement is in

    BasicBlock *thenB = BasicBlock::Create(context.llvmContext, "then", theFunction);
    BasicBlock *elseB = BasicBlock::Create(context.llvmContext, "else");
    BasicBlock *condB = BasicBlock::Create(context.llvmContext, "cond");

    if (falseBlock) {
        context.builder.CreateCondBr(cond, thenB, elseB);
    } else {
        context.builder.CreateCondBr(cond, thenB, condB);
    }

    context.builder.SetInsertPoint(thenB);
    context.pushCodeBlock(thenB);
    trueBlock->generateCode(context);
    context.popCurrentCodeBlock();
    thenB = context.builder.GetInsertBlock();

    if (!thenB->getTerminator()) {       //
        context.builder.CreateBr(condB);
    }

    if (falseBlock) {
        theFunction->getBasicBlockList().push_back(elseB);    //
        context.builder.SetInsertPoint(elseB);            //
        context.pushCodeBlock(elseB);
        falseBlock->generateCode(context);
        context.popCurrentCodeBlock();
        context.builder.CreateBr(condB);
    }

    theFunction->getBasicBlockList().push_back(condB);        //
    context.builder.SetInsertPoint(condB);        //

    return nullptr;
}

ValuePtr WhileStatementNode::generateCode(CodeGenerationContext &context) const {

    Function *theFunction = context.builder.GetInsertBlock()->getParent();

    BasicBlock *loopB = BasicBlock::Create(context.llvmContext, "whileLoop", theFunction);
    BasicBlock *condB = BasicBlock::Create(context.llvmContext, "whileCond");

    Value *cond = condition->generateCode(context);
    if (!cond)
        return nullptr;

    cond = CastToBoolean(context, cond);

    // fall to the loopB
    context.builder.CreateCondBr(cond, loopB, condB);
    context.builder.SetInsertPoint(loopB);
    context.pushCodeBlock(loopB);
    block->generateCode(context);
    context.popCurrentCodeBlock();

    // execute the again or stop
    cond = condition->generateCode(context);
    cond = CastToBoolean(context, cond);
    context.builder.CreateCondBr(cond, loopB, condB);

    // insert the condB loopB
    theFunction->getBasicBlockList().push_back(condB);
    context.builder.SetInsertPoint(condB);

    return nullptr;
}

ValuePtr ReturnStatementNode::generateCode(CodeGenerationContext &context) const {
    if (expr) {
        ValuePtr value = expr->generateCode(context);
        context.setCurrentReturnValue(value);
        return value;
    } else {
        return nullptr;
    }
}
