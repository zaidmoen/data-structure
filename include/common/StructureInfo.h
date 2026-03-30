#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ds {

struct ComplexityProfile {
    string access;
    string search;
    string insert;
    string remove;
    string traversal;
    string notes;
};

struct StructureInfo {
    string name;
    string category;
    string description;
    string ordering;
    string storage_model;
    string growth_model;
    string duplicates;
    string typical_use;
    ComplexityProfile complexities;
    vector<string> strengths;
    vector<string> weaknesses;
};

inline void PrintList(ostream& output, const vector<string>& items) {
    if (items.empty()) {
        output << "  - None\n";
        return;
    }

    for (const string& item : items) {
        output << "  - " << item << endl;
    }
}

inline void PrintStructureInfo(const StructureInfo& info, ostream& output = cout) {
    output << "============================================================\n";
    output << info.name << " [" << info.category << "]\n";
    output << "Description     : " << info.description << endl;
    output << "Ordering        : " << info.ordering << endl;
    output << "Storage         : " << info.storage_model << endl;
    output << "Growth          : " << info.growth_model << endl;
    output << "Duplicates      : " << info.duplicates << endl;
    output << "Typical use     : " << info.typical_use << endl;
    output << "Complexities    :\n";
    output << "  - Access    : " << info.complexities.access << endl;
    output << "  - Search    : " << info.complexities.search << endl;
    output << "  - Insert    : " << info.complexities.insert << endl;
    output << "  - Remove    : " << info.complexities.remove << endl;
    output << "  - Traversal : " << info.complexities.traversal << endl;
    output << "  - Notes     : " << info.complexities.notes << endl;
    output << "Strengths       :\n";
    PrintList(output, info.strengths);
    output << "Weaknesses      :\n";
    PrintList(output, info.weaknesses);
    output << endl;
}

}  // namespace ds
