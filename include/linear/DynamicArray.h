#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename T>
class DynamicArray {
public:
    static StructureInfo GetInfo() {
        return {
            "Dynamic Array",
            "Linear",
            "Contiguous storage that grows automatically when capacity is exhausted.",
            "Maintains insertion order by index.",
            "Contiguous memory block.",
            "Resizes geometrically; appends are amortized constant time.",
            "Allowed.",
            "Fast indexed access, appending elements, and cache-friendly iteration.",
            {"O(1)", "O(n)", "O(1) amortized at end, O(n) in the middle", "O(n)", "O(n)",
             "Occasional resize copies many elements at once."},
            {"Fast random access.", "Works well with CPU cache.", "Simple iteration model."},
            {"Middle insertions shift elements.", "Resizing can invalidate references."}
        };
    }

    void push_back(const T& value) {
        arr.push_back(value);
    }

    void insert(int index, const T& value) {
        if (index > arr.size()) {
            throw out_of_range("DynamicArray insert index out of range");
        }
        arr.insert(arr.begin() + index, value);
    }

    void remove_at(int index) {
        if (index >= arr.size()) {
            throw out_of_range("DynamicArray remove index out of range");
        }
        arr.erase(arr.begin() + index);
    }

    T& at(int index) {
        return arr.at(index);
    }

    const T& at(int index) const {
        return arr.at(index);
    }

    bool empty() const {
        return arr.empty();
    }

    int size() const {
        return arr.size();
    }

    const vector<T>& data() const {
        return arr;
    }

private:
    vector<T> arr;
};

}  // namespace ds
