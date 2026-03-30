#pragma once

#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T, int MinDegree = 2>
class BTree {
    static_assert(MinDegree >= 2, "BTree MinDegree must be at least 2");

public:
    BTree() : root(make_unique<Node>(true)) {}

    static StructureInfo GetInfo() {
        return {
            "B-Tree",
            "Tree",
            "Balanced multi-way search tree designed to keep height small even with many keys.",
            "Ordered by key value across nodes and children.",
            "Nodes store multiple sorted keys and multiple child pointers.",
            "Grows by splitting full nodes on the insertion path.",
            "This implementation ignores duplicates.",
            "Databases, file systems, and storage engines where reducing height is important.",
            {"O(log n)", "O(log n)", "O(log n)", "Commonly O(log n) when implemented", "O(n)",
             "Wide branching factor makes disk-oriented access efficient."},
            {"Keeps height very small.", "Excellent for block and page storage systems."},
            {"More complex node logic than binary trees.", "Node splitting is harder to implement and debug."}
        };
    }

    void insert(const T& key) {
        if (contains(key)) {
            return;
        }

        if (root->keys.size() == MaxKeys()) {
            auto new_root = make_unique<Node>(false);
            new_root->children.push_back(move(root));
            SplitChild(new_root.get(), 0U);
            root = move(new_root);
        }

        InsertNonFull(root.get(), key);
    }

    bool contains(const T& key) const {
        return Contains(root.get(), key);
    }

    vector<T> inorder() const {
        vector<T> values;
        Inorder(root.get(), values);
        return values;
    }

private:
    struct Node {
        bool leaf;
        vector<T> keys;
        vector<unique_ptr<Node>> children;

        explicit Node(bool is_leaf) : leaf(is_leaf) {}
    };

    static constexpr int MaxKeys() {
        return static_cast<int>(2 * MinDegree - 1);
    }

    static void SplitChild(Node* parent, int index) {
        Node* full_child = parent->children[index].get();
        auto sibling = make_unique<Node>(full_child->leaf);
        const T middle_key = full_child->keys[static_cast<int>(MinDegree - 1)];

        for (int key_index = static_cast<int>(MinDegree); key_index < full_child->keys.size(); key_index++) {
            sibling->keys.push_back(move(full_child->keys[key_index]));
        }
        full_child->keys.resize(static_cast<int>(MinDegree - 1));

        if (!full_child->leaf) {
            for (int child_index = static_cast<int>(MinDegree); child_index < full_child->children.size(); child_index++) {
                sibling->children.push_back(move(full_child->children[child_index]));
            }
            full_child->children.resize(static_cast<int>(MinDegree));
        }

        parent->children.insert(parent->children.begin() + index + 1,
                                move(sibling));
        parent->keys.insert(parent->keys.begin() + index, middle_key);
    }

    static void InsertNonFull(Node* node, const T& key) {
        if (node->leaf) {
            auto position = lower_bound(node->keys.begin(), node->keys.end(), key);
            node->keys.insert(position, key);
            return;
        }

        auto position = lower_bound(node->keys.begin(), node->keys.end(), key);
        int child_index = static_cast<int>(position - node->keys.begin());

        if (node->children[child_index]->keys.size() == MaxKeys()) {
            SplitChild(node, child_index);
            if (key > node->keys[child_index]) {
                ++child_index;
            }
        }

        InsertNonFull(node->children[child_index].get(), key);
    }

    static bool Contains(const Node* node, const T& key) {
        if (node == nullptr) {
            return false;
        }

        auto position = lower_bound(node->keys.begin(), node->keys.end(), key);
        const int key_index = static_cast<int>(position - node->keys.begin());

        if (position != node->keys.end() && *position == key) {
            return true;
        }
        if (node->leaf) {
            return false;
        }
        return Contains(node->children[key_index].get(), key);
    }

    static void Inorder(const Node* node, vector<T>& values) {
        if (node == nullptr) {
            return;
        }

        for (int index = 0; index < node->keys.size(); index++) {
            if (!node->leaf) {
                Inorder(node->children[index].get(), values);
            }
            values.push_back(node->keys[index]);
        }

        if (!node->leaf) {
            Inorder(node->children.back().get(), values);
        }
    }

    unique_ptr<Node> root;
};

}  // namespace ds
