#pragma once

#include <deque>
#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class Deque {
public:
    static StructureInfo GetInfo() {
        return {
            "Deque",
            "Linear",
            "Double-ended queue that supports insertion and removal at both ends.",
            "Maintains sequence order while exposing both front and back as active ends.",
            "Often implemented with a block-based deque or doubly linked list.",
            "Grows and shrinks at either end.",
            "Allowed.",
            "Sliding windows, task schedulers, palindrome checks, and monotonic queues.",
            {"O(1) for front/back", "O(n)", "O(1) at either end", "O(1) at either end", "O(n)",
             "Middle operations are still linear."},
            {"Flexible two-end updates.", "Good base for both stack and queue behavior."},
            {"Middle search remains linear.", "Implementation is heavier than a stack or queue."}
        };
    }

    void push_front(const T& value) {
        arr.push_front(value);
    }

    void push_back(const T& value) {
        arr.push_back(value);
    }

    void pop_front() {
        if (arr.empty()) {
            throw underflow_error("Deque is empty");
        }
        arr.pop_front();
    }

    void pop_back() {
        if (arr.empty()) {
            throw underflow_error("Deque is empty");
        }
        arr.pop_back();
    }

    const T& front() const {
        if (arr.empty()) {
            throw underflow_error("Deque is empty");
        }
        return arr.front();
    }

    const T& back() const {
        if (arr.empty()) {
            throw underflow_error("Deque is empty");
        }
        return arr.back();
    }

    bool empty() const {
        return arr.empty();
    }

    int size() const {
        return arr.size();
    }

    vector<T> snapshot() const {
        return vector<T>(arr.begin(), arr.end());
    }

private:
    deque<T> arr;
};

}  // namespace ds
