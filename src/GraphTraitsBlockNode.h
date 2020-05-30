//
// Created by 郑文浩 on 2020/5/29.
//

#ifndef COMPILER_GRAPHTRAITSBLOCKNODE_H
#define COMPILER_GRAPHTRAITSBLOCKNODE_H

#include <llvm/ADT/GraphTraits.h>

#include "ast.h"

using namespace llvm;

template<>
struct GraphTraits<BlockNode *> {
    using NodeRef = ASTNode *;

    class NodeIterator {
        int index = 0;
        ASTNode *node = nullptr;
        NodeIterator *parent;

        void findChild() {
            while (node->getChildrenNumber()) {
                parent = new NodeIterator(node, index, parent);
                index = 0;
                node = node->getChildren(index);
            }
        };
    public:
        NodeIterator(ASTNode *node, int index, NodeIterator *parent) : node(node), index(index), parent(parent) {};

        NodeIterator(ASTNode *node) : node(node), index(0), parent(nullptr) {
            findChild();
        };

        NodeIterator(NodeIterator const &iterator) = default;

        ~NodeIterator() = default;

        NodeIterator &operator++() {
            if (index + 1 < node->getChildrenNumber()) {
                index++;
                findChild();
                return *this;
            } else {
                if (parent) {
                    NodeIterator *parent = this->parent;
                    delete this;
                    return parent->operator++();
                } else {
                    node = nullptr;
                    index = 0;
                    return *this;
                }
            }
        };

        ASTNode &operator*() {
            return *node;
        }

        ASTNode *operator->() {
            return &(operator*());
        }

        bool operator==(const NodeIterator &iterator) const {
            return node == iterator.node && index == iterator.index && parent == iterator.parent;
        }

        bool operator!=(const NodeIterator &iterator) const { return !operator==(iterator); }
    };

};

#endif //COMPILER_GRAPHTRAITSBLOCKNODE_H
