#pragma once

#include <memory>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class BinarySearchTree {
public:
    static StructureInfo GetInfo() {
        return {
            "Binary Search Tree",
            "Tree",
            "Binary tree that keeps smaller keys on the left and larger keys on the right.",
            "Ordered by key value through the BST invariant.",
            "Linked binary nodes.",
            "Grows one node at a time; shape depends on insertion order.",
            "This implementation ignores duplicates.",
            "Ordered sets/maps, range queries, and sorted traversal with simple recursion.",
            {"O(log n) average, O(n) worst", "O(log n) average, O(n) worst", "O(log n) average, O(n) worst",
             "O(log n) average, O(n) worst", "O(n)", "Performance collapses when the tree becomes skewed."},
            {"Inorder traversal is naturally sorted.", "Simple recursive insert/search/remove."},
            {"Can degrade to a linked list without balancing.", "Insertion order matters a lot."}
        };
    }

    void insert(const T& value) {
        Insert(root, value);
    }

    bool contains(const T& value) const {
        return Contains(root, value);
    }

    void remove(const T& value) {
        Remove(root, value);
    }

    vector<T> inorder() const {
        vector<T> values;
        Inorder(root, values);
        return values;
    }

private:
    struct Node {
        T value;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        explicit Node(const T& new_value) : value(new_value) {}
    };

    static void Insert(unique_ptr<Node>& node, const T& value) {
        if (node == nullptr) {
            node = make_unique<Node>(value);
            return;
        }

        if (value < node->value) {
            Insert(node->left, value);
        } else if (value > node->value) {
            Insert(node->right, value);
        }
    }

    static bool Contains(const unique_ptr<Node>& node, const T& value) {
        if (node == nullptr) {
            return false;
        }
        if (value == node->value) {
            return true;
        }
        if (value < node->value) {
            return Contains(node->left, value);
        }
        return Contains(node->right, value);
    }

    static void Remove(unique_ptr<Node>& node, const T& value) {
        if (node == nullptr) {
            return;
        }

        if (value < node->value) {
            Remove(node->left, value);
            return;
        }
        if (value > node->value) {
            Remove(node->right, value);
            return;
        }

        if (node->left == nullptr) {
            node = move(node->right);
            return;
        }
        if (node->right == nullptr) {
            node = move(node->left);
            return;
        }

        Node* successor = node->right.get();
        while (successor->left != nullptr) {
            successor = successor->left.get();
        }

        node->value = successor->value;
        Remove(node->right, successor->value);
    }

    static void Inorder(const unique_ptr<Node>& node, vector<T>& values) {
        if (node == nullptr) {
            return;
        }
        Inorder(node->left, values);
        values.push_back(node->value);
        Inorder(node->right, values);
    }

    unique_ptr<Node> root;
};

}  // namespace ds
