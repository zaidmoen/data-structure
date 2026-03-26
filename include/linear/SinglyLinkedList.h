#pragma once

#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class SinglyLinkedList {
public:
    struct Node {
        T value;
        Node* next;

        explicit Node(const T& new_value) : value(new_value), next(nullptr) {}
    };

    SinglyLinkedList() = default;

    ~SinglyLinkedList() {
        clear();
    }

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    static StructureInfo GetInfo() {
        return {
            "Singly Linked List",
            "Linear",
            "Sequence of nodes where each node stores a value and a pointer to the next node.",
            "Maintains link order but has no indexed ordering guarantee.",
            "Non-contiguous nodes connected with one-way links.",
            "Grows one node at a time without relocation.",
            "Allowed.",
            "Frequent insertions at the front or streaming data where random access is not required.",
            {"O(n)", "O(n)", "O(1) at head, O(1) at tail with tail pointer, O(n) by position", "O(1) at head, O(n) elsewhere",
             "O(n)", "Excellent when node moves are cheaper than array shifts."},
            {"Cheap head insertion.", "No reallocation when growing.", "Stable node addresses."},
            {"No random access.", "Extra memory for pointers.", "Reverse traversal is not direct."}
        };
    }

    void push_front(const T& value) {
        Node* node = new Node(value);
        node->next = head;
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
        ++currentSize;
    }

    void push_back(const T& value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        ++currentSize;
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }

        Node* old_head = head;
        head = head->next;
        delete old_head;
        --currentSize;

        if (head == nullptr) {
            tail = nullptr;
        }
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
