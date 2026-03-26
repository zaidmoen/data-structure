#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class Stack {
public:
    static StructureInfo GetInfo() {
        return {
            "Stack",
            "Linear",
            "Last-in, first-out collection where insertions and deletions happen at one end only.",
            "Ordered by push history; top element is the newest element.",
            "Usually backed by an array or linked list.",
            "Grows from one logical end.",
            "Allowed.",
            "Function calls, backtracking, expression evaluation, and undo behavior.",
            {"O(1) for top only", "O(n)", "O(1)", "O(1)", "O(n)",
             "Only the top is directly accessible."},
            {"Very simple API.", "Fast push/pop.", "Natural fit for nested workflows."},
            {"No fast search.", "Cannot access middle elements directly."}
        };
    }

    void push(const T& value) {
        arr.push_back(value);
    }

    void pop() {
        if (arr.empty()) {
            throw underflow_error("Stack is empty");
        }
        arr.pop_back();
    }

    const T& top() const {
        if (arr.empty()) {
            throw underflow_error("Stack is empty");
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
        return arr;
    }

private:
    vector<T> arr;
};

}  // namespace ds
