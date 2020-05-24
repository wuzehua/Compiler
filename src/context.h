#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
//#include <json/json.h>

#include <stack>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "ast.h"
#include "syn.hpp"
#include "type_system.h"

using namespace llvm;
using std::unique_ptr;
using std::string;

using SymTable = std::map<string, Value *>;

class CodeGenBlock {
public:
    BasicBlock *block;
    Value *returnValue;
    std::map<string, Value *> localVars;
    std::map<string, shared_ptr<IdentifierNode>> types;     // type name string of vars
    std::map<string, bool> isFuncArg;
    std::map<string, std::vector<uint64_t>> arraySizes;
};

class CodeGenerationContext {
private:
    std::vector<CodeGenBlock *> blockVector;

public:
    LLVMContext llvmContext;
    IRBuilder<> builder;
    unique_ptr<Module> theModule;
    SymTable globalVars;
    TypeSystem typeSystem;

    CodeGenerationContext() : builder(llvmContext), typeSystem(llvmContext) {
        theModule = unique_ptr<Module>(new Module("main", this->llvmContext));
    }

    Value *getSymbolValue(string name) const {
        for (auto it = blockVector.rbegin(); it != blockVector.rend(); it++) {
            if ((*it)->localVars.find(name) != (*it)->localVars.end()) {
                return (*it)->localVars[name];
            }
        }
        return nullptr;
    }

    shared_ptr<IdentifierNode> getSymbolType(string name) const {
        for (auto it = blockVector.rbegin(); it != blockVector.rend(); it++) {
            if ((*it)->types.find(name) != (*it)->types.end()) {
                return (*it)->types[name];
            }
        }
        return nullptr;
    }

    bool isFuncArg(string name) const {
        for (auto it = blockVector.rbegin(); it != blockVector.rend(); it++) {
            if ((*it)->isFuncArg.find(name) != (*it)->isFuncArg.end()) {
                return (*it)->isFuncArg[name];
            }
        }
        return false;
    }

    void setSymbolValue(string name, Value *value) {
        if (blockVector.back()->localVars.find(name) != blockVector.back()->localVars.end()) {
            blockVector.back()->localVars[name] = value;
        }
    }

    void setSymbolType(string name, shared_ptr<IdentifierNode> value) {
        if (blockVector.back()->types.find(name) != blockVector.back()->types.end()) {
            blockVector.back()->types[name] = value;
        }
    }

    void setFuncArg(string name, bool value) {
        if (blockVector.back()->isFuncArg.find(name) != blockVector.back()->isFuncArg.end()) {
            blockVector.back()->isFuncArg[name] = value;
        }
    }

    BasicBlock *currentBlock() const {
        if (blockVector.empty()) {
            return nullptr;
        }
        return blockVector.back()->block;
    }

    void pushBlock(BasicBlock *block) {
        CodeGenBlock *codeGenBlock = new CodeGenBlock();
        codeGenBlock->block = block;
        codeGenBlock->returnValue = nullptr;
        blockVector.push_back(codeGenBlock);
    }

    void popBlock() {
        if (blockVector.empty()) {
            return;
        }
        CodeGenBlock *codeGenBlock = blockVector.back();
        blockVector.pop_back();
        delete codeGenBlock;
    }

    void setCurrentReturnValue(Value *value) {
        if (blockVector.empty()) {
            return;
        }
        blockVector.back()->returnValue = value;
    }

    Value *getCurrentReturnValue() {
        if (blockVector.empty()) {
            return nullptr;
        }
        return blockVector.back()->returnValue;
    }

    void setArraySize(string name, std::vector<uint64_t> value) {
        if (blockVector.back()->arraySizes.find(name) != blockVector.back()->arraySizes.end()) {
            blockVector.back()->arraySizes[name] = value;
        }
    }

    std::vector<uint64_t> getArraySize(string name) {
        for (auto it = blockVector.rbegin(); it != blockVector.rend(); it++) {
            if ((*it)->arraySizes.find(name) != (*it)->arraySizes.end()) {
                return (*it)->arraySizes[name];
            }
        }
        return std::vector<uint64_t>();
    }

    void PrintSymTable() const {
        std::cout << "======= Print Symbol Table ========" << std::endl;
        string prefix = "";
        for (auto it = blockVector.begin(); it != blockVector.end(); it++) {
            for (auto it2 = (*it)->localVars.begin(); it2 != (*it)->localVars.end(); it2++) {
                std::cout << prefix << it2->first << " = " << it2->second << ": " << this->getSymbolType(it2->first)
                          << std::endl;
            }
            prefix += "\t";
        }
        std::cout << "===================================" << std::endl;
    }

    void generateCode(BlockNode &);

};

#endif