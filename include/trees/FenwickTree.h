#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

class FenwickTree {
public:
    FenwickTree() = default;

    explicit FenwickTree(int size) : tree_(size + 1, 0) {}

    explicit FenwickTree(const vector<int>& values) : tree_(values.size() + 1, 0) {
        for (int index = 0; index < values.size(); index++) {
            add(index, values[index]);
        }
    }

    static StructureInfo GetInfo() {
        return {
            "Fenwick Tree",
            "Tree",
            "Binary indexed tree that stores partial sums for fast prefix and range aggregation.",
            "Ordered by array index.",
            "Compact array with implicit parent-child relationships.",
            "Built from array updates that propagate through indexed ranges.",
            "Duplicates depend on the source array values.",
            "Prefix sums, range sums, and frequency tables with low memory overhead.",
            {"O(1) for size", "O(log n) prefix query", "O(log n) point update", "O(log n) via negative update", "O(n)",
             "Often simpler and smaller than a segment tree for prefix-style operations."},
            {"Compact memory footprint.", "Very fast prefix and range sum operations."},
            {"Less flexible than a segment tree for arbitrary range operations.", "Indexing details can be tricky."}
        };
    }

    void add(int index, int delta) {
        if (index >= size()) {
            throw out_of_range("FenwickTree update index out of range");
        }

        for (int cursor = index + 1; cursor < tree_.size(); cursor += LowBit(cursor)) {
            tree_[cursor] += delta;
        }
    }

    int prefix_sum(int index) const {
        if (index >= size()) {
            throw out_of_range("FenwickTree prefix_sum index out of range");
        }

        int total = 0;
        for (int cursor = index + 1; cursor > 0U; cursor -= LowBit(cursor)) {
            total += tree_[cursor];
        }
        return total;
    }

    int range_sum(int left, int right) const {
        if (left > right || right >= size()) {
            throw out_of_range("FenwickTree range_sum range is invalid");
        }

        return prefix_sum(right) - (left == 0U ? 0 : prefix_sum(left - 1));
    }

    int size() const {
        return tree_.empty() ? 0U : tree_.size() - 1;
    }

private:
    static int LowBit(int value) {
        return value & (~value + 1);
    }

    vector<int> tree_;
};

}  // namespace ds
