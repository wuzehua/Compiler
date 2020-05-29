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
#include <stack>
#include "ast.h"
#include "syn.hpp"
#include "type_helper.h"

using namespace llvm;
using std::unique_ptr;
using std::string;
using std::map;
using std::vector;


struct Symbol{
    ValuePtr variable = nullptr;
    shared_ptr<TypeNode> type = nullptr;
};

struct CodeBlock{
    BasicBlock* block;
    map<string, struct Symbol> symbolTable;
    struct CodeBlock* next;

    explicit CodeBlock(BasicBlock* block):
                block(block),
                next(nullptr){}

    [[nodiscard]]
    Symbol* findSymbol(const string& name) const {
        auto iter = symbolTable.find(name);
        if(iter != symbolTable.end()){
            return (Symbol*)&(iter->second);
        }

        return nullptr;
    }


    void createSymbol(const string& name){
        Symbol symbol;
        symbolTable.insert({name, symbol});
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

    [[nodiscard]]
    Symbol* findSymbolInCurrentBlock(const string& name) const {
        Symbol* symbol = nullptr;
        if(currentBlock != nullptr){
            symbol = currentBlock->findSymbol(name);
        }
        return symbol;
    }



public:
    LLVMContext llvmContext;
    IRBuilder<> builder;
    unique_ptr<Module> theModule;
    TypeHelper typeHelper;


    CodeGenerationContext() : builder(llvmContext), typeHelper(llvmContext) {
        theModule = std::make_unique<Module>("main", this->llvmContext);
        globalBlock = nullptr;
        currentBlock = nullptr;
    }

    ~CodeGenerationContext(){
        while(currentBlock != nullptr){
            auto temp = currentBlock;
            currentBlock = currentBlock->next;
            delete temp;
        }
    }

    [[nodiscard]]
    ValuePtr getSymbolValue(const string& name) const {
        Symbol* symbol = findSymbol(name);
        return symbol == nullptr ? nullptr : symbol->variable;
    }

    [[nodiscard]]
    shared_ptr<TypeNode> getSymbolType(const string& name) const {
        Symbol* symbol = findSymbol(name);
        return symbol == nullptr ? nullptr : symbol->type;
    }



    void createSymbol(const string& name){
        assert(currentBlock != nullptr);
        Symbol* symbol = findSymbolInCurrentBlock(name);
        if(symbol == nullptr){
            currentBlock->createSymbol(name);
        }
    }

    void setSymbolValue(const string& name, ValuePtr value) {
        Symbol* symbol = findSymbol(name);
        if (symbol != nullptr){
            symbol->variable = value;
        }
    }

    void setSymbolType(const string& name, const shared_ptr<TypeNode>& value) {
        Symbol* symbol = findSymbol(name);
        if (symbol != nullptr){
            symbol->type = value;
        }
    }


    bool isInGlobalBlock(){
        return globalBlock != nullptr && currentBlock == globalBlock;
    }


    [[nodiscard]]
    BasicBlock* getCurrentBasicBlock() const {
        return currentBlock != nullptr ? currentBlock->block : nullptr;
    }

    void setCurrentBlock(BasicBlock* block){
        if(currentBlock != nullptr){
            currentBlock->block = block;
        }
    }

    void pushCodeBlock(BasicBlock* block){
        auto codeBlock = new CodeBlock(block);
        if(globalBlock == nullptr){
            globalBlock = codeBlock;
        }else{
            codeBlock->next = currentBlock;
        }
        currentBlock = codeBlock;
    }

    void popCurrentCodeBlock(){
        if(currentBlock != nullptr){
            auto temp = currentBlock;
            currentBlock = currentBlock->next;
            delete temp;
            if(currentBlock == nullptr){
                globalBlock = nullptr;
            }
        }
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
            for(auto & it : temp->symbolTable){
                const Symbol& symbol = it.second;
                std::cout<<it.first<<": Var("<<symbol.variable<<") ";
                if(symbol.type){
                    std::cout<<"Type(name:"<<symbol.type->name<<", isArray:"<<symbol.type->isArray<<")\n";
                }
            }

            std::cout<<'\n';
            index += 1;
            temp = temp->next;
        }
    }

    void generateCode(BlockNode* blockNode);

    void exportToObj(const string& filename);


};
