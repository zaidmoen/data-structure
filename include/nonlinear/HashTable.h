#pragma once

#include <functional>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

template <typename Key, typename Value, typename Hash = hash<Key>>
class HashTable {
public:
    explicit HashTable(int bucket_count = 17U) : buckets_(bucket_count == 0U ? 17U : bucket_count) {}

    static StructureInfo GetInfo() {
        return {
            "Hash Table",
            "Non-Linear",
            "Associative container that maps keys to buckets using a hash function.",
            "Unordered by default; physical order depends on hash distribution.",
            "Bucket array with chained collision lists.",
            "Can grow by increasing bucket count and rehashing.",
            "Keys are unique in this implementation.",
            "Fast key lookup, caching, indexing, and symbol tables.",
            {"N/A by index", "O(1) average, O(n) worst case", "O(1) average, O(n) worst case", "O(1) average, O(n) worst case",
             "O(n)", "Quality of the hash function strongly affects performance."},
            {"Very fast average lookup.", "Excellent for exact-key searches.", "Scales well with good hashing."},
            {"Does not keep sorted order.", "Worst case degrades when collisions are heavy.", "Rehashing can be expensive."}
        };
    }

    void insert(const Key& key, const Value& value) {
        auto& bucket = buckets_[BucketIndex(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }

        bucket.emplace_back(key, value);
        ++currentSize;
    }

    bool contains(const Key& key) const {
        const auto& bucket = buckets_[BucketIndex(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return true;
            }
        }
        return false;
    }

    Value& at(const Key& key) {
        auto& bucket = buckets_[BucketIndex(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        throw out_of_range("HashTable key not found");
    }

    const Value& at(const Key& key) const {
        const auto& bucket = buckets_[BucketIndex(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        throw out_of_range("HashTable key not found");
    }

    bool remove(const Key& key) {
        auto& bucket = buckets_[BucketIndex(key)];
        for (auto iterator = bucket.begin(); iterator != bucket.end(); iterator++) {
            if (iterator->first == key) {
                bucket.erase(iterator);
                --currentSize;
                return true;
            }
        }
        return false;
    }

    int size() const {
        return currentSize;
    }

private:
    int BucketIndex(const Key& key) const {
        return hasher_(key) % buckets_.size();
    }

    vector<list<pair<Key, Value>>> buckets_;
    int currentSize = 0U;
    Hash hasher_;
};

}  // namespace ds
