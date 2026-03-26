#pragma once

#include <deque>
#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class Queue {
public:
    static StructureInfo GetInfo() {
        return {
            "Queue",
            "Linear",
            "First-in, first-out collection where insertions occur at the back and removals occur at the front.",
            "Ordered by arrival time.",
            "Commonly backed by a circular buffer, deque, or linked list.",
            "Grows from the back and shrinks from the front.",
            "Allowed.",
            "Scheduling, buffering, task processing, and breadth-first traversal.",
            {"O(1) for front/back", "O(n)", "O(1)", "O(1)", "O(n)",
             "Preserves fairness by processing earliest elements first."},
            {"Natural pipeline model.", "Fast enqueue/dequeue.", "Excellent for producer-consumer flows."},
            {"No random access.", "Searching is linear."}
        };
    }

    void enqueue(const T& value) {
        arr.push_back(value);
    }

    void dequeue() {
        if (arr.empty()) {
            throw underflow_error("Queue is empty");
        }
        arr.pop_front();
    }

    const T& front() const {
        if (arr.empty()) {
            throw underflow_error("Queue is empty");
        }
        return arr.front();
    }

    const T& back() const {
        if (arr.empty()) {
            throw underflow_error("Queue is empty");
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
