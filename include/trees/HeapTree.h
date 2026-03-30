#pragma once

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T, typename Compare = less<T>>
class HeapTree {
public:
    explicit HeapTree(Compare compare = Compare()) : compare_(compare) {}

    static StructureInfo GetInfo() {
        return {
            "Heap Tree",
            "Tree",
            "Complete binary tree stored in an array where each parent has priority over its children.",
            "Partially ordered only; siblings and cousins are not globally sorted.",
            "Contiguous array representation.",
            "Grows by appending and restoring heap order with sift operations.",
            "Allowed.",
            "Priority queues, scheduling, Dijkstra-like algorithms, and repeated min/max extraction.",
            {"O(1) for top", "O(n)", "O(log n)", "O(log n) for pop", "O(n)",
             "Choose the comparator to make it a min-heap or max-heap."},
            {"Fast access to the best-priority element.", "Array storage is compact and cache-friendly."},
            {"Only the root is globally meaningful.", "Full sorted traversal requires repeated pops."}
        };
    }

    void push(const T& value) {
        arr.push_back(value);
        SiftUp(arr.size() - 1);
    }

    void pop() {
        if (arr.empty()) {
            throw underflow_error("HeapTree is empty");
        }

        swap(arr.front(), arr.back());
        arr.pop_back();
        if (!arr.empty()) {
            SiftDown(0U);
        }
    }

    const T& top() const {
        if (arr.empty()) {
            throw underflow_error("HeapTree is empty");
        }
        return arr.front();
    }

    bool empty() const {
        return arr.empty();
    }

    int size() const {
        return arr.size();
    }

    vector<T> as_array() const {
        return arr;
    }

private:
    bool HasHigherPriority(const T& left, const T& right) const {
        return compare_(left, right);
    }

    void SiftUp(int index) {
        while (index > 0U) {
            const int parent = (index - 1) / 2U;
            if (!HasHigherPriority(arr[index], arr[parent])) {
                break;
            }
            swap(arr[index], arr[parent]);
            index = parent;
        }
    }

    void SiftDown(int index) {
        while (true) {
            const int left = index * 2U + 1;
            const int right = index * 2U + 2U;
            int best = index;

            if (left < arr.size() && HasHigherPriority(arr[left], arr[best])) {
                best = left;
            }
            if (right < arr.size() && HasHigherPriority(arr[right], arr[best])) {
                best = right;
            }
            if (best == index) {
                break;
            }

            swap(arr[index], arr[best]);
            index = best;
        }
    }

    vector<T> arr;
    Compare compare_;
};

}  // namespace ds
