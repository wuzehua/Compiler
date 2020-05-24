#pragma once

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <memory>
#include <utility>
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
using std::map;
using std::vector;


struct Symbol{
    ValuePtr variable;
    bool isFunctionArgs;
    shared_ptr<IdentifierNode> type;
    vector<uint64_t> size;

};

struct CodeBlock{
    BasicBlock* block;
    ValuePtr returnValue;
    map<string, struct Symbol> symbolTable;
    struct CodeBlock* next;

    explicit CodeBlock(BasicBlock* block):
                block(block),
                returnValue(nullptr),
                next(nullptr){}

    [[nodiscard]]
    Symbol* findSymbol(const string& name) const {
        auto iter = symbolTable.find(name);
        if(iter != symbolTable.end()){
            return (Symbol*)&(iter->second);
        }

        return nullptr;
    }
};

class CodeGenerationContext {
private:
    CodeBlock* globalBlock;
    CodeBlock* currentBlock;


    [[nodiscard]]
    Symbol* findSymbol(const string& name) const {
        auto tempBlock = currentBlock;
        Symbol* symbol = nullptr;
        while (tempBlock != nullptr){
            symbol = tempBlock->findSymbol(name);
            if(symbol != nullptr){
                break;
            }
            tempBlock = tempBlock->next;
        }
        return symbol;
    }

public:
    LLVMContext llvmContext;
    IRBuilder<> builder;
    unique_ptr<Module> theModule;
    TypeSystem typeSystem;


    CodeGenerationContext() : builder(llvmContext), typeSystem(llvmContext) {
        theModule = std::make_unique<Module>("main", this->llvmContext);
        globalBlock = nullptr;
        currentBlock = nullptr;
    }

    [[nodiscard]]
    ValuePtr getSymbolValue(const string& name) const {
        Symbol* symbol = findSymbol(name);
        return symbol == nullptr ? nullptr : symbol->variable;
    }

    [[nodiscard]]
    shared_ptr<IdentifierNode> getSymbolType(const string& name) const {
        Symbol* symbol = findSymbol(name);
        return symbol == nullptr ? nullptr : symbol->type;
    }


    [[nodiscard]]
    bool isFuncArg(const string& name) const {
        Symbol* symbol = findSymbol(name);
        return symbol == nullptr ? false : symbol->isFunctionArgs;
    }

    void setSymbolValue(const string& name, ValuePtr value) {
        Symbol* symbol = findSymbol(name);
        if (symbol != nullptr){
            symbol->variable = value;
        }
    }

    void setSymbolType(const string& name, shared_ptr<IdentifierNode> value) {
        Symbol* symbol = findSymbol(name);
        if (symbol != nullptr){
            symbol->type = std::move(value);
        }
    }

    void setFuncArg(const string& name, bool value) {
        Symbol* symbol = findSymbol(name);
        if (symbol != nullptr){
            symbol->isFunctionArgs = value;
        }
    }




    [[nodiscard]]
    BasicBlock* getCurrentBasicBlock() const {
        return currentBlock != nullptr ? currentBlock->block : nullptr;
    }

    void addCodeBlock(BasicBlock* block){
        auto codeBlock = new CodeBlock(block);
        if(globalBlock == nullptr){
            globalBlock = codeBlock;
            currentBlock = codeBlock;
        }else{
            codeBlock->next = currentBlock;
            currentBlock = codeBlock;
        }
    }

    void removeCurrentCodeBlock(){
        if(currentBlock != nullptr){
            auto temp = currentBlock;
            currentBlock = currentBlock->next;
            delete temp;
            if(currentBlock == nullptr){
                globalBlock = nullptr;
            }
        }
    }


    void setCurrentReturnValue(ValuePtr value) {
        if(currentBlock != nullptr){
            currentBlock->returnValue = value;
        }
    }

    ValuePtr getCurrentReturnValue() {
        return currentBlock != nullptr ? currentBlock->returnValue : nullptr;
    }

    void setArraySize(const string& name, std::vector<uint64_t> value) {
        Symbol* symbol = findSymbol(name);
        if(symbol != nullptr){
            symbol->size = std::move(value);
        }
    }

    std::vector<uint64_t> getArraySize(const string& name) {
        Symbol* symbol = findSymbol(name);
        return symbol != nullptr ? symbol->size : std::vector<uint64_t>();
    }

    void PrintSymTable() const {
        std::cout << "[Symbol Table]\n\n";
        auto temp = currentBlock;
        int index = 0;
        while (temp != nullptr){
            if(temp == globalBlock){
                std::cout<<"[Global Block]\n";
            }else {
                std::cout << "[Block " << index << "]\n";
            }
            for(auto & it : currentBlock->symbolTable){
                const Symbol& symbol = it.second;
                std::cout<<it.first<<": Var("<<symbol.variable<<") isFuncArgs("<<symbol.isFunctionArgs<<") ";
                if(symbol.type){
                    std::cout<<"Type(name:"<<symbol.type->name<<", isArray:"<<symbol.type->isArray<<", isType:"<<symbol.type->isType<<")\n";
                }
            }

            std::cout<<'\n';
            index += 1;
            temp = temp->next;
        }
    }

    void generateCode(BlockNode* blockNode);

};
