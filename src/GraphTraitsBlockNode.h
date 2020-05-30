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
        int index;
        NodeRef node;
        NodeIterator *parent;

        void findChild() {
            while (node->getChildrenNumber()) {
                if (index == -1) {
                    index = 0;
                }
                parent = new NodeIterator(node, index, parent);
                index = -1;
                node = node->getChildren(0);
            }
        };
    public:
        NodeIterator(NodeRef node, int index, NodeIterator *parent) : node(node), index(index), parent(parent) {};

        NodeIterator(NodeRef node) : node(node), index(0), parent(nullptr) {
            findChild();
        };

        NodeIterator(const NodeIterator &iterator) = default;

        ~NodeIterator() = default;

        static NodeIterator getBeginIterator(NodeRef node) {
            return NodeIterator(node);
        }

        static NodeIterator getEndIterator(NodeRef node) {
            return NodeIterator(node, node->getChildrenNumber(), nullptr);
        }

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
                    index = node->getChildrenNumber();
                    return *this;
                }
            }
        };

        NodeRef operator*() {
            return node;
        }

        bool operator==(const NodeIterator &iterator) const {
            return node == iterator.node && index == iterator.index && parent == iterator.parent;
        }

        bool operator!=(const NodeIterator &iterator) const { return !operator==(iterator); }
    };

    class ChildIterator {
        NodeRef node = nullptr;
        int index;
    public:
        ChildIterator(NodeRef node, int index = -1) : node(node), index(index) {
            if (node->getChildrenNumber() && index == -1) {
                index = 0;
            }
        };

        ChildIterator(const ChildIterator &iterator) = default;

        ~ChildIterator() = default;

        static ChildIterator getBeginIterator(NodeRef node) {
            return ChildIterator(node);
        }

        static ChildIterator getEndIterator(NodeRef node) {
            ChildIterator iterator(node);
            iterator.index = iterator.node->getChildrenNumber();
            return iterator;
        }

        ChildIterator &operator++() {
            if (index < node->getChildrenNumber()) {
                index++;
            }
            return *this;
        };

        NodeRef operator*() {
            return node->getChildren(index);
        }

        bool operator==(const ChildIterator &iterator) const {
            return node == iterator.node && index == iterator.index;
        }

        bool operator!=(const ChildIterator &iterator) const { return !operator==(iterator); }
    };

    using nodes_iterator = NodeIterator;

    using ChildIteratorType = ChildIterator;

    static nodes_iterator nodes_begin(BlockNode *G) {
        return nodes_iterator::getBeginIterator(G);
    };

    static nodes_iterator nodes_end(BlockNode *G) {
        return nodes_iterator::getEndIterator(G);
    };

    static ChildIteratorType child_begin(NodeRef node) {
        return ChildIteratorType::getBeginIterator(node);
    }

    static ChildIteratorType child_end(NodeRef node) {
        return ChildIteratorType::getEndIterator(node);
    }

};

#endif //COMPILER_GRAPHTRAITSBLOCKNODE_H
