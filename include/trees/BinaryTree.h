#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class BinaryTree {
public:
    struct Node {
        T value;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        explicit Node(const T& new_value) : value(new_value) {}
    };

    static StructureInfo GetInfo() {
        return {
            "Binary Tree",
            "Tree",
            "Hierarchical structure where each node has at most two children.",
            "No automatic sorting unless additional rules are imposed.",
            "Linked nodes with left and right child pointers.",
            "Grows by attaching nodes to the left or right of an existing parent.",
            "Allowed unless the application forbids them.",
            "Expression trees, parse trees, and as a base for BSTs, heaps, and balanced trees.",
            {"O(n)", "O(n)", "O(1) when parent slot is known", "O(size of removed subtree)", "O(n)",
             "Traversal can be preorder, inorder, postorder, or level order."},
            {"Simple recursive structure.", "Foundation for many advanced tree types."},
            {"No guaranteed balance or ordering.", "Search is linear without ordering rules."}
        };
    }

    Node* set_root(const T& value) {
        root_ = make_unique<Node>(value);
        return root_.get();
    }

    Node* root() {
        return root_.get();
    }

    const Node* root() const {
        return root_.get();
    }

    Node* insert_left(Node* parent, const T& value) {
        if (parent == nullptr) {
            throw invalid_argument("BinaryTree parent cannot be null");
        }
        if (parent->left != nullptr) {
            throw logic_error("BinaryTree left child already exists");
        }

        parent->left = make_unique<Node>(value);
        return parent->left.get();
    }

    Node* insert_right(Node* parent, const T& value) {
        if (parent == nullptr) {
            throw invalid_argument("BinaryTree parent cannot be null");
        }
        if (parent->right != nullptr) {
            throw logic_error("BinaryTree right child already exists");
        }

        parent->right = make_unique<Node>(value);
        return parent->right.get();
    }

    vector<T> preorder() const {
        vector<T> values;
        Preorder(root_.get(), values);
        return values;
    }

    vector<T> inorder() const {
        vector<T> values;
        Inorder(root_.get(), values);
        return values;
    }

    vector<T> postorder() const {
        vector<T> values;
        Postorder(root_.get(), values);
        return values;
    }

private:
    static void Preorder(const Node* node, vector<T>& values) {
        if (node == nullptr) {
            return;
        }
        values.push_back(node->value);
        Preorder(node->left.get(), values);
        Preorder(node->right.get(), values);
    }

    static void Inorder(const Node* node, vector<T>& values) {
        if (node == nullptr) {
            return;
        }
        Inorder(node->left.get(), values);
        values.push_back(node->value);
        Inorder(node->right.get(), values);
    }

    static void Postorder(const Node* node, vector<T>& values) {
        if (node == nullptr) {
            return;
        }
        Postorder(node->left.get(), values);
        Postorder(node->right.get(), values);
        values.push_back(node->value);
    }

    unique_ptr<Node> root_;
};

}  // namespace ds
