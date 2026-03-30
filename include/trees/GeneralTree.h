#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class GeneralTree {
public:
    struct Node {
        T value;
        vector<unique_ptr<Node>> children;

        explicit Node(const T& new_value) : value(new_value) {}
    };

    static StructureInfo GetInfo() {
        return {
            "General Tree",
            "Tree",
            "Hierarchical tree where every node may have any number of children.",
            "Parent-child order may exist, but there is no binary or sorted constraint.",
            "Nodes with variable-size child lists.",
            "Grows by attaching children to any existing node.",
            "Allowed unless the application forbids them.",
            "Organization charts, file systems, DOM-like hierarchies, and category trees.",
            {"O(n)", "O(n)", "O(1) to attach a child when parent is known", "O(size of removed subtree)", "O(n)",
             "Traversal order depends on the chosen strategy such as preorder or level order."},
            {"Models natural hierarchies well.", "Flexible number of children per node."},
            {"Searching is usually linear without extra indexing.", "Child count variability complicates some algorithms."}
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

    Node* add_child(Node* parent, const T& value) {
        if (parent == nullptr) {
            throw invalid_argument("GeneralTree parent cannot be null");
        }

        parent->children.push_back(make_unique<Node>(value));
        return parent->children.back().get();
    }

    vector<T> preorder() const {
        vector<T> values;
        Preorder(root_.get(), values);
        return values;
    }

private:
    static void Preorder(const Node* node, vector<T>& values) {
        if (node == nullptr) {
            return;
        }

        values.push_back(node->value);
        for (const auto& child : node->children) {
            Preorder(child.get(), values);
        }
    }

    unique_ptr<Node> root_;
};

}  // namespace ds
