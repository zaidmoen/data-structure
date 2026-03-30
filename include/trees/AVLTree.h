#pragma once

#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class AVLTree {
public:
    static StructureInfo GetInfo() {
        return {
            "AVL Tree",
            "Tree",
            "Self-balancing BST that keeps subtree heights close using rotations.",
            "Ordered by key value like a BST.",
            "Linked binary nodes with an extra height field.",
            "Grows one node at a time and may rotate after updates.",
            "This implementation ignores duplicates.",
            "When you need consistently fast ordered lookup with stricter balance than a plain BST.",
            {"O(log n)", "O(log n)", "O(log n)", "Commonly O(log n) when implemented", "O(n)",
             "Maintaining balance gives faster worst-case search than a plain BST."},
            {"Guaranteed logarithmic height.", "Inorder traversal stays sorted."},
            {"More complex than a normal BST.", "Rotations add implementation cost."}
        };
    }

    void insert(const T& value) {
        root = Insert(move(root), value);
    }

    bool contains(const T& value) const {
        return Contains(root, value);
    }

    vector<T> inorder() const {
        vector<T> values;
        Inorder(root, values);
        return values;
    }

private:
    struct Node {
        T value;
        int height = 1;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        explicit Node(const T& new_value) : value(new_value) {}
    };

    static int Height(const unique_ptr<Node>& node) {
        return node == nullptr ? 0 : node->height;
    }

    static void UpdateHeight(unique_ptr<Node>& node) {
        node->height = 1 + max(Height(node->left), Height(node->right));
    }

    static int BalanceFactor(const unique_ptr<Node>& node) {
        return node == nullptr ? 0 : Height(node->left) - Height(node->right);
    }

    static unique_ptr<Node> RotateRight(unique_ptr<Node> node) {
        auto new_root = move(node->left);
        node->left = move(new_root->right);
        UpdateHeight(node);
        new_root->right = move(node);
        UpdateHeight(new_root->right);
        UpdateHeight(new_root);
        return new_root;
    }

    static unique_ptr<Node> RotateLeft(unique_ptr<Node> node) {
        auto new_root = move(node->right);
        node->right = move(new_root->left);
        UpdateHeight(node);
        new_root->left = move(node);
        UpdateHeight(new_root->left);
        UpdateHeight(new_root);
        return new_root;
    }

    static unique_ptr<Node> Rebalance(unique_ptr<Node> node) {
        UpdateHeight(node);
        const int balance = Height(node->left) - Height(node->right);

        if (balance > 1) {
            if (BalanceFactor(node->left) < 0) {
                node->left = RotateLeft(move(node->left));
            }
            return RotateRight(move(node));
        }

        if (balance < -1) {
            if (BalanceFactor(node->right) > 0) {
                node->right = RotateRight(move(node->right));
            }
            return RotateLeft(move(node));
        }

        return node;
    }

    static unique_ptr<Node> Insert(unique_ptr<Node> node, const T& value) {
        if (node == nullptr) {
            return make_unique<Node>(value);
        }

        if (value < node->value) {
            node->left = Insert(move(node->left), value);
        } else if (value > node->value) {
            node->right = Insert(move(node->right), value);
        } else {
            return node;
        }

        return Rebalance(move(node));
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
