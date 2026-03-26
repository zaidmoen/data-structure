#pragma once

#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T value;
        Node* previous;
        Node* next;

        explicit Node(const T& new_value) : value(new_value), previous(nullptr), next(nullptr) {}
    };

    DoublyLinkedList() = default;

    ~DoublyLinkedList() {
        clear();
    }

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    static StructureInfo GetInfo() {
        return {
            "Doubly Linked List",
            "Linear",
            "Sequence of nodes where each node points to both its previous and next neighbor.",
            "Maintains link order and supports two-way traversal.",
            "Non-contiguous nodes connected with forward and backward links.",
            "Grows one node at a time without moving existing nodes.",
            "Allowed.",
            "Deque-like operations, undo/redo chains, and bidirectional traversal.",
            {"O(n)", "O(n)", "O(1) at known ends or known node, O(n) by position", "O(1) at known ends or known node, O(n) by position",
             "O(n)", "Uses more pointer memory than a singly linked list."},
            {"Easy front and back updates.", "Bidirectional traversal.", "Good base for deque behavior."},
            {"No direct indexed access.", "Two pointers per node increase memory use."}
        };
    }

    void push_front(const T& value) {
        Node* node = new Node(value);
        node->next = head;

        if (head != nullptr) {
            head->previous = node;
        } else {
            tail = node;
        }

        head = node;
        ++currentSize;
    }

    void push_back(const T& value) {
        Node* node = new Node(value);
        node->previous = tail;

        if (tail != nullptr) {
            tail->next = node;
        } else {
            head = node;
        }

        tail = node;
        ++currentSize;
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }

        Node* old_head = head;
        head = head->next;

        if (head != nullptr) {
            head->previous = nullptr;
        } else {
            tail = nullptr;
        }

        delete old_head;
        --currentSize;
    }

    void pop_back() {
        if (tail == nullptr) {
            return;
        }

        Node* old_tail = tail;
        tail = tail->previous;

        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete old_tail;
        --currentSize;
    }

    bool contains(const T& value) const {
        for (Node* current = head; current != nullptr; current = current->next) {
            if (current->value == value) {
                return true;
            }
        }
        return false;
    }

    vector<T> to_vector() const {
        vector<T> values;
        values.reserve(currentSize);
        for (Node* current = head; current != nullptr; current = current->next) {
            values.push_back(current->value);
        }
        return values;
    }

    bool empty() const {
        return currentSize == 0U;
    }

    int size() const {
        return currentSize;
    }

    void clear() {
        while (head != nullptr) {
            pop_front();
        }
    }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int currentSize = 0U;
};

}  // namespace ds
