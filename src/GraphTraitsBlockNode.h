//
// Created by 郑文浩 on 2020/5/29.
//

#ifndef COMPILER_GRAPHTRAITSBLOCKNODE_H
#define COMPILER_GRAPHTRAITSBLOCKNODE_H

#include <llvm/ADT/GraphTraits.h>

#include "ast.h"

using namespace llvm;

class NodeIterator {
    int index = 0;
    ASTNode *node = nullptr;
    NodeIterator *parent;
public:
    NodeIterator(ASTNode *node, int index, NodeIterator *parent = nullptr) : node(node), index(index),
                                                                             parent(parent) {};

    NodeIterator(NodeIterator const &iterator) = default;

    ~NodeIterator() = default;

    NodeIterator &operator++() {
        if (index < node->getChildrenNumber() - 1) {
            index++;
            return *this;
        } else if (parent) {
            return parent->operator++();
        }
    };
};

template<>
struct GraphTraits<BlockNode *> {
    using NodeRef = ASTNode *;

};

#endif //COMPILER_GRAPHTRAITSBLOCKNODE_H
