#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

class SegmentTree {
public:
    SegmentTree() = default;

    explicit SegmentTree(const vector<int>& values) {
        build(values);
    }

    static StructureInfo GetInfo() {
        return {
            "Segment Tree",
            "Tree",
            "Binary tree over ranges that supports fast range queries and point updates.",
            "Ordered by array index ranges.",
            "Usually stored in an array representing tree nodes.",
            "Built from an existing array and updated by propagating changes along a path.",
            "Duplicates depend on the source array values.",
            "Range sums, minimum queries, interval statistics, and competitive programming problems.",
            {"O(1) for root aggregate", "O(log n) range query", "O(log n) point update", "O(log n) point update", "O(n)",
             "This implementation stores range sums."},
            {"Excellent range-query performance.", "Supports updates much faster than recomputing whole ranges."},
            {"Uses more memory than the raw array.", "Implementation is less intuitive than a prefix sum array."}
        };
    }

    void build(const vector<int>& values) {
        arr = values;
        currentSize = arr.size();

        if (currentSize == 0U) {
            tree_.clear();
            return;
        }

        tree_.assign(currentSize * 4U, 0);
        Build(1, 0U, currentSize - 1);
    }

    int range_sum(int left, int right) const {
        ValidateRange(left, right);
        return Query(1, 0U, currentSize - 1, left, right);
    }

    void update(int index, int value) {
        if (index >= currentSize) {
            throw out_of_range("SegmentTree update index out of range");
        }
        arr[index] = value;
        Update(1, 0U, currentSize - 1, index, value);
    }

    int size() const {
        return currentSize;
    }

private:
    void ValidateRange(int left, int right) const {
        if (currentSize == 0U) {
            throw out_of_range("SegmentTree is empty");
        }
        if (left > right || right >= currentSize) {
            throw out_of_range("SegmentTree query range is invalid");
        }
    }

    void Build(int node, int left, int right) {
        if (left == right) {
            tree_[node] = arr[left];
            return;
        }

        const int middle = left + (right - left) / 2U;
        Build(node * 2U, left, middle);
        Build(node * 2U + 1, middle + 1, right);
        tree_[node] = tree_[node * 2U] + tree_[node * 2U + 1];
    }

    int Query(int node, int left, int right, int query_left,
              int query_right) const {
        if (query_left <= left && right <= query_right) {
            return tree_[node];
        }

        const int middle = left + (right - left) / 2U;
        int total = 0;

        if (query_left <= middle) {
            total += Query(node * 2U, left, middle, query_left, query_right);
        }
        if (query_right > middle) {
            total += Query(node * 2U + 1, middle + 1, right, query_left, query_right);
        }

        return total;
    }

    void Update(int node, int left, int right, int index, int value) {
        if (left == right) {
            tree_[node] = value;
            return;
        }

        const int middle = left + (right - left) / 2U;
        if (index <= middle) {
            Update(node * 2U, left, middle, index, value);
        } else {
            Update(node * 2U + 1, middle + 1, right, index, value);
        }

        tree_[node] = tree_[node * 2U] + tree_[node * 2U + 1];
    }

    vector<int> arr;
    vector<int> tree_;
    int currentSize = 0U;
};

}  // namespace ds
