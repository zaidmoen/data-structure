#pragma once

#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

class Trie {
public:
    Trie() : root(make_unique<Node>()) {}

    static StructureInfo GetInfo() {
        return {
            "Trie",
            "Tree",
            "Prefix tree where each edge represents part of a key, usually one character.",
            "Ordered by shared prefixes, not by full key comparison.",
            "Nodes with sparse character transitions.",
            "Grows by adding new characters only where needed.",
            "Repeated words can be handled through terminal counts; this version tracks presence only.",
            "Autocomplete, dictionaries, prefix filters, and lexicon matching.",
            {"O(length)", "O(length)", "O(length)", "Commonly O(length) when implemented", "O(total characters)",
             "Time depends on key length rather than number of stored words."},
            {"Excellent prefix queries.", "Shared prefixes reduce repeated storage."},
            {"Can use significant memory for sparse alphabets.", "Not ideal for arbitrary ordering by value."}
        };
    }

    void insert(const string& word) {
        Node* current = root.get();
        for (char character : word) {
            auto& next = current->children[character];
            if (next == nullptr) {
                next = make_unique<Node>();
            }
            current = next.get();
        }
        current->is_terminal = true;
    }

    bool contains(const string& word) const {
        const Node* node = Navigate(word);
        return node != nullptr && node->is_terminal;
    }

    bool starts_with(const string& prefix) const {
        return Navigate(prefix) != nullptr;
    }

private:
    struct Node {
        bool is_terminal = false;
        unordered_map<char, unique_ptr<Node>> children;
    };

    const Node* Navigate(const string& text) const {
        const Node* current = root.get();
        for (char character : text) {
            const auto iterator = current->children.find(character);
            if (iterator == current->children.end()) {
                return nullptr;
            }
            current = iterator->second.get();
        }
        return current;
    }

    unique_ptr<Node> root;
};

}  // namespace ds
