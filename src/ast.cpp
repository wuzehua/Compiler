#include <llvm/IR/Type.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include "llvm/ADT/APFloat.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <string>
#include <functional>

#include "ast.h"
#include "context.h"


ValuePtr IntegerNode::generateCode(CodeGenerationContext &context) const {
    Log::raiseMessage("Generating Integer Const");
    Type *type = Type::getInt64Ty(context.llvmContext); //设置返回值的类型为int32
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr CharNode::generateCode(CodeGenerationContext &context) const {
    Log::raiseMessage("Generating Char Const");
    Type *type = Type::getInt16Ty(context.llvmContext);
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr RealNode::generateCode(CodeGenerationContext &context) const {
    Log::raiseMessage("Generating Real Const");
    Type *type = Type::getDoubleTy(context.llvmContext);
    return llvm::ConstantFP::get(type, value);
}

ValuePtr BoolNode::generateCode(CodeGenerationContext &context) const {
    Log::raiseMessage("Generating Bool Const");
    Type *type = Type::getInt1Ty(context.llvmContext);
    return llvm::ConstantInt::get(type, value, true);
}

ValuePtr IdentifierNode::generateCode(CodeGenerationContext &context) const {
    ValuePtr value = context.getSymbolValue(name);
    if (!value) {
        Log::raiseError("Unknown variable name " + this->name, std::cout);
        return nullptr;
    }

    if (value->getType()->isPointerTy()) {
        auto valuePtr = context.builder.CreateLoad(value, "valuePtr");
        if (valuePtr->getType()->isArrayTy()) {
            std::vector<ValuePtr> index;
            index.emplace_back(ConstantInt::get(Type::getInt32PtrTy(context.llvmContext), 0, false));
            return context.builder.CreateInBoundsGEP(value, index, "valuePtr");
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
        return nullptr;
    }

    if ((calleeF->arg_size() != 0 && !args) || (args && calleeF->arg_size() != args->size())) {
        Log::raiseError("Function args number not match, " + id->name + " requires " + std::to_string(calleeF->size()) +
                        "args, but " + std::to_string(args ? args->size() : 0) + "args are given", std::cout);
        return nullptr;
    }

    std::vector<ValuePtr> argsList;

    if (args) {
        for (auto &it : *args) {
            auto argPtr = it->generateCode(context);
            if (!argPtr) {
                return nullptr;
            } else {
                argsList.emplace_back(argPtr);
            }
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
    exp = context.typeHelper.cast(exp, context.typeHelper.getLLVMVarType(context.getSymbolType(id->name)->name),
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
        Log::raiseError(id->name + " is not an array", std::cout);
        return nullptr;
    }

    return context.builder.CreateAlignedLoad(context.builder.CreateInBoundsGEP(var, indices, "elementPtr"),
                                             MaybeAlign());
}

ValuePtr ArrayIndexAssignmentNode::generateCode(CodeGenerationContext &context) const {
    auto var = context.getSymbolValue(element->id->name);
    auto type = context.getSymbolType(element->id->name);

    if (!var) {
        Log::raiseError("Undefined variable", std::cout);
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

    Log::raiseMessage("Start generating variable declaration node for " + id->name, std::cout);

    TypePtr typePtr = context.typeHelper.getLLVMVarType(type->name);

    if (typePtr == nullptr) {
        Log::raiseError("Type " + type->name + " is not defined.", std::cout);
        return nullptr;
    }

    Log::raiseMessage("Type is " + TypeHelper::llvmTypeToStr(typePtr), std::cout);


    ValuePtr cd;
    if (type->isArray) {
        uint64_t arraySize = 1;
        std::vector<uint64_t> arraySizes;
        auto *integer = dynamic_cast<IntegerNode *>(type->arraySize.get());
        arraySize *= integer->value;
        arraySizes.emplace_back(integer->value);

        context.setArraySize(id->name, arraySizes);
        Value *arraySizeValue = IntegerNode(arraySize).generateCode(context);
        auto arrayType = ArrayType::get(context.typeHelper.getLLVMVarType(type->name), arraySize);
        cd = context.builder.CreateAlloca(arrayType, arraySizeValue, "arraytmp");

    } else {
        if (context.isInGlobalBlock()) {
            auto globalVar = new GlobalVariable(typePtr, false, GlobalValue::InternalLinkage);
            context.theModule->getGlobalList().push_back(globalVar);
            cd = globalVar;
        } else {
            Log::raiseMessage("Creating Alloca for " + id->name, std::cout);
            cd = context.builder.CreateAlloca(typePtr, nullptr, id->name);
            Log::raiseMessage("Finish creating Alloca for " + id->name, std::cout);
        }
    }

    Log::raiseMessage("Finish creating IR for variable " + id->name, std::cout);

    context.createSymbol(id->name);
    context.setSymbolType(id->name, type);
    context.setSymbolValue(id->name, cd);


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
    Type *retTp = context.typeHelper.getLLVMType(type);

    std::vector<TypePtr> argsTypeVec;

    for (auto &it : *this->args)
        argsTypeVec.emplace_back(context.typeHelper.getLLVMVarType(it->type->name));

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
        llvmargs_it->setName((*args_it)->id->name);
        ValuePtr val;
        if ((*args_it)->type->isArray)
            val = context.builder.CreateAlloca(
                    PointerType::get(context.typeHelper.getLLVMVarType((*args_it)->type->name), 0), 0U);
        else
            val = (*args_it)->generateCode(context);
        context.builder.CreateStore(llvmargs_it, val, false);
        context.createSymbol((*args_it)->id->name);
        context.setFuncArg((*args_it)->id->name, true);
        context.setSymbolValue((*args_it)->id->name, val);
        context.setSymbolType((*args_it)->id->name, (*args_it)->type);
    }

    context.PrintSymTable();

    block->generateCode(context);
//    if (context.getCurrentReturnValue()) {
//        context.builder.CreateRet(context.getCurrentReturnValue());
//    } else {
//        if(retTp->isVoidTy()){
//            context.builder.CreateRetVoid();
//        }else {
//            Log::raiseError("Function block return value not founded", std::cout);
//            //return nullptr;
//        }
//    }

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

    if (!thenB->getTerminator()) {
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

    return nullptr;
}

ValuePtr WhileStatementNode::generateCode(CodeGenerationContext &context) const {

    Function *theFunction = context.builder.GetInsertBlock()->getParent();

    BasicBlock *loopB = BasicBlock::Create(context.llvmContext, "whileLoop", theFunction);
    BasicBlock *condB = BasicBlock::Create(context.llvmContext, "whileCond");

    Value *cond = condition->generateCode(context);
    if (!cond)
        return nullptr;

    cond = TypeHelper::castCondition(context, cond);
    if (!cond) {
        return nullptr;
    }

    // fall to the loopB
    context.builder.CreateCondBr(cond, loopB, condB);
    context.builder.SetInsertPoint(loopB);
    context.pushCodeBlock(loopB);
    block->generateCode(context);
    context.popCurrentCodeBlock();

    // execute the again or stop
    cond = condition->generateCode(context);
    cond = TypeHelper::castCondition(context, cond);
    context.builder.CreateCondBr(cond, loopB, condB);

    // insert the condB loopB
    theFunction->getBasicBlockList().push_back(condB);
    context.builder.SetInsertPoint(condB);

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
