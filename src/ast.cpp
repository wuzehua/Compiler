#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/ADT/APFloat.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <string>
#include <functional>

#include "ast.h"
#include "context.h"


ValuePtr IntegerNode::generateCode(CodeGenerationContext &context) const {
    Type *type = Type::getInt64Ty(context.llvmContext); //设置返回值的类型为int32
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
    ValuePtr value = context.getSymbolValue(name);
    if (!value) {
        Log::raiseError("Unknown variable name " + this->name, std::cout);
        return nullptr;
    }

    if(value->getType()->isPointerTy()){
        Log::raiseWarning("Access array pointer is not supported yet.", std::cout);
        return nullptr;
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


    bool bothFloat = false;

    if (opL->getType()->isDoubleTy() || opR->getType()->isDoubleTy()) {
        bothFloat = true;
        if (!(opL->getType()->isDoubleTy())) {
            opL = context.builder.CreateSIToFP(opL, Type::getDoubleTy(context.llvmContext), "fopL");
        }

        if (!(opR->getType()->isDoubleTy())) {
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
        case yytokentype::MOD:
            if(!bothFloat) {
                return context.builder.CreateSRem(opL, opR, "IMod");
            }else{
                Log::raiseError("Only Integer type can operate REM operation!", std::cout);
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
        Log::raiseError("Function " + id->name + " is not found", std::cout);
        return nullptr;
    }

    if (calleeF->arg_size() != args->size()) {
        Log::raiseError("Function args number not match, " + id->name + " requires " + std::to_string(calleeF->size()) +
                        "args, but " + std::to_string(args ? args->size() : 0) + "args are given", std::cout);
        return nullptr;
    }

    std::vector<ValuePtr> argsList;


    for (auto &it : *args) {
        auto argPtr = it->generateCode(context);
        if (!argPtr) {
            return nullptr;
        } else {
            argsList.emplace_back(argPtr);
        }
    }


    return context.builder.CreateCall(calleeF, argsList);
}

ValuePtr AssignmentNode::generateCode(CodeGenerationContext &context) const {
    auto var = context.getSymbolValue(id->name);
    if (!var) {
        Log::raiseError("AssignmentNode: Undefined variable " + id->name, std::cout);
        return nullptr;
    }

    ValuePtr exp = expr->generateCode(context);
    exp = context.typeHelper.cast(exp, context.typeHelper.getLLVMVarType(context.getSymbolType(id->name)->name),
                                  context.getCurrentBasicBlock());
    context.builder.CreateStore(exp, var);
    return var;
}

ValuePtr ArrayIndexNode::generateCode(CodeGenerationContext &context) const {
    auto var = context.getSymbolValue(id->name);
    auto type = context.getSymbolType(id->name);

    if (!var) {
        Log::raiseError("ArrayIndex: Undefined variable " + id->name, std::cout);
        return nullptr;
    }

    if (!type->isArray) {
        Log::raiseError(id->name + " is not an array", std::cout);
        return nullptr;
    }

    auto value = index->generateCode(context);
    ArrayRef<ValuePtr> indices;
    indices = {ConstantInt::get(Type::getInt64Ty(context.llvmContext), 0), value};


    return context.builder.CreateAlignedLoad(context.builder.CreateInBoundsGEP(var, indices, "elementPtr"),
                                             MaybeAlign());
}

ValuePtr ArrayIndexAssignmentNode::generateCode(CodeGenerationContext &context) const {
    auto var = context.getSymbolValue(element->id->name);
    auto type = context.getSymbolType(element->id->name);

    if (!var) {
        Log::raiseError("ArrayIndexAssignment: Undefined variable " + element->id->name, std::cout);
        return nullptr;
    }

    auto arrVar = context.builder.CreateLoad(var, "arrayPtr");

    if (!arrVar->getType()->isArrayTy() && !arrVar->getType()->isPointerTy()) {
        Log::raiseError(element->id->name + " is not an array", std::cout);
        return nullptr;
    }

    auto index = element->index->generateCode(context);
    ArrayRef<ValuePtr> indices = {ConstantInt::get(Type::getInt64Ty(context.llvmContext), 0), index};

    auto val = expr->generateCode(context);

    return context.builder.CreateAlignedStore(val, context.builder.CreateInBoundsGEP(var, indices, "elementPtr"),
                                              MaybeAlign());
}

ValuePtr BlockNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr value = nullptr;
    for (const auto &statement : this->statements)
        value = statement->generateCode(context);
    return value;
}

ValuePtr VariableDeclarationNode::generateCode(CodeGenerationContext &context) const {

    TypePtr typePtr = context.typeHelper.getLLVMVarType(type->name);

    if (typePtr == nullptr) {
        Log::raiseError("Type " + type->name + " is not defined.", std::cout);
        return nullptr;
    }

    context.createSymbol(id->name);

    ValuePtr cd;

    if (type->isArray) {
        uint64_t arraySize = type->arraySize->value;

        TypePtr lengthType = Type::getInt64Ty(context.llvmContext);
        ValuePtr arraySizePtr = ConstantInt::get(lengthType, arraySize);

        typePtr = ArrayType::get(typePtr, arraySize);

    }

    if(context.isInGlobalBlock()){
        Constant* initial = nullptr;
        if(type->isArray == false){
            initial = context.typeHelper.getDefaultValue(type->name);
        }else{
            initial = ConstantAggregateZero::get(typePtr);
        }
        auto globalVar = new GlobalVariable(*context.theModule,typePtr, false, GlobalValue::CommonLinkage,initial, id->name);    
        cd = globalVar;
    }else{
        cd = context.builder.CreateAlloca(typePtr, nullptr, id->name);
    }


    context.setSymbolType(id->name, type);
    context.setSymbolValue(id->name, cd);


    if (assignmentExpr) {
        ValuePtr assignVal = assignmentExpr->generateCode(context);
        assignVal = context.typeHelper.cast(assignVal, typePtr, context.getCurrentBasicBlock());
        context.builder.CreateStore(assignVal, cd);
    }

    return cd;
}

ValuePtr ExpressionStatementNode::generateCode(CodeGenerationContext &context) const {
    return expr->generateCode(context);
}

ValuePtr FunctionDeclarationNode::generateCode(CodeGenerationContext &context) const {
    TypePtr retTp = context.typeHelper.getLLVMType(type);

    std::vector<TypePtr> argsTypeVec;

    for (auto &it : *args)
        argsTypeVec.emplace_back(context.typeHelper.getLLVMType(it->type));

    FunctionType *thisFuncType = FunctionType::get(retTp, argsTypeVec, false);

    Function *thisFunc = Function::Create(thisFuncType, Function::ExternalLinkage, this->id->name,
                                          context.theModule.get());
    if (external) {
        return thisFunc;
    }

    BasicBlock *funcBlock = BasicBlock::Create(context.llvmContext, "entry", thisFunc);
    context.builder.SetInsertPoint(funcBlock);
    context.pushCodeBlock(funcBlock);


    auto args_it = this->args->begin();
    auto llvmargs_it = thisFunc->args().begin();
    for (; args_it != this->args->end() && llvmargs_it != thisFunc->args().end(); ++args_it, ++llvmargs_it) {
        ValuePtr val = (*args_it)->generateCode(context);
        context.builder.CreateStore(llvmargs_it, val);
    }


    block->generateCode(context);
    
    if(context.getCurrentBasicBlock()->getTerminator() == nullptr){
        if(retTp->getTypeID() == Type::VoidTyID){
            context.builder.CreateRetVoid();
        }else{
            ValuePtr retVal = context.typeHelper.getDefaultValue(type->name);
            context.builder.CreateRet(retVal);
        }
    }

    context.popCurrentCodeBlock();

    return thisFunc;
}


ValuePtr IfStatementNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr cond = condition->generateCode(context);
    if (!cond)
        return nullptr;

    cond = TypeHelper::castCondition(context, cond);

    if (!cond) {
        return nullptr;
    }

    Function *theFunction = context.builder.GetInsertBlock()->getParent();

    BasicBlock *thenB = BasicBlock::Create(context.llvmContext, "then", theFunction);
    BasicBlock *elseB = BasicBlock::Create(context.llvmContext, "else");
    BasicBlock *condB = BasicBlock::Create(context.llvmContext, "merge");

    if (falseBlock) {
        context.builder.CreateCondBr(cond, thenB, elseB);
    } else {
        context.builder.CreateCondBr(cond, thenB, condB);
    }

    context.builder.SetInsertPoint(thenB);
    context.pushCodeBlock(thenB);
    trueBlock->generateCode(context);
    context.popCurrentCodeBlock();

    if(thenB->getTerminator() == nullptr){
        context.builder.CreateBr(condB);
    }


    if (falseBlock) {
        theFunction->getBasicBlockList().push_back(elseB);
        context.builder.SetInsertPoint(elseB);
        context.pushCodeBlock(elseB);
        falseBlock->generateCode(context);
        context.popCurrentCodeBlock();
        context.builder.CreateBr(condB);
    }

    theFunction->getBasicBlockList().push_back(condB);
    context.builder.SetInsertPoint(condB);
    context.setCurrentBlock(condB);

    return nullptr;
}

ValuePtr WhileStatementNode::generateCode(CodeGenerationContext &context) const {

    Function *theFunction = context.builder.GetInsertBlock()->getParent();

    BasicBlock *condB = BasicBlock::Create(context.llvmContext, "whileCond");
    BasicBlock *loopB = BasicBlock::Create(context.llvmContext, "whileLoop");
    BasicBlock *finalB = BasicBlock::Create(context.llvmContext, "final");

    context.builder.CreateBr(condB);

    theFunction->getBasicBlockList().push_back(loopB);
    context.builder.SetInsertPoint(loopB);
    context.pushCodeBlock(loopB);
    block->generateCode(context);
    context.popCurrentCodeBlock();
    context.builder.CreateBr(condB);


    theFunction->getBasicBlockList().push_back(condB);
    context.builder.SetInsertPoint(condB);

    if(!condition){
        Log::raiseError("No condition found in the While Loop", std::cout);
        return nullptr;
    }

    
    ValuePtr cond = condition->generateCode(context);
    cond = TypeHelper::castCondition(context, cond);

    if(cond == nullptr){
        return nullptr;
    }

    context.builder.CreateCondBr(cond, loopB, finalB);

    theFunction->getBasicBlockList().push_back(finalB);
    context.builder.SetInsertPoint(finalB);
    context.setCurrentBlock(finalB);

    return nullptr;
}

ValuePtr ReturnStatementNode::generateCode(CodeGenerationContext &context) const {
    if (expr) {
        ValuePtr value = expr->generateCode(context);
        context.builder.CreateRet(value);
        return value;
    } else {
        context.builder.CreateRetVoid();
        return nullptr;
    }
}
