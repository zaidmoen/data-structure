#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "include/common/StructureInfo.h"
#include "include/linear/Deque.h"
#include "include/linear/DoublyLinkedList.h"
#include "include/linear/DynamicArray.h"
#include "include/linear/Queue.h"
#include "include/linear/SinglyLinkedList.h"
#include "include/linear/Stack.h"
#include "include/nonlinear/Graph.h"
#include "include/nonlinear/HashTable.h"
#include "include/trees/AVLTree.h"
#include "include/trees/BTree.h"
#include "include/trees/BinarySearchTree.h"
#include "include/trees/BinaryTree.h"
#include "include/trees/FenwickTree.h"
#include "include/trees/GeneralTree.h"
#include "include/trees/HeapTree.h"
#include "include/trees/SegmentTree.h"
#include "include/trees/TreeFamilies.h"
#include "include/trees/Trie.h"

template <typename T>
void PrintValues(const string& label, const vector<T>& values) {
    cout << label << ": ";
    if (values.empty()) {
        cout << "(empty)\n";
        return;
    }

    for (int index = 0; index < values.size(); index++) {
        cout << values[index];
        if (index + 1 < values.size()) {
            cout << " | ";
        }
    }
    cout << endl;
}

string BoolText(bool value) {
    return value ? "Yes" : "No";
}

void PrintTitle(const string& title) {
    cout << "\n############################################################\n";
    cout << title << endl;
    cout << "############################################################\n\n";
}

int main() {
    // Main function starts here
    using namespace ds;
    using namespace std;

    cout << "Data Structures Reference Project\n";
    cout << "One main.cpp with separate header files for each structure.\n";
    cout << "The output shows ordering, behavior, complexity, and a short demo.\n";

    PrintTitle("Linear Structures");

    PrintStructureInfo(DynamicArray<int>::GetInfo());
    DynamicArray<int> dynamic_array;
    dynamic_array.push_back(10);
    dynamic_array.push_back(30);
    dynamic_array.insert(1, 20);
    dynamic_array.remove_at(0);
    PrintValues("DynamicArray values", dynamic_array.data());
    cout << "Access index 1: " << dynamic_array.at(1) << endl << endl;

    PrintStructureInfo(SinglyLinkedList<int>::GetInfo());
    SinglyLinkedList<int> singly_list;
    singly_list.push_front(10);
    singly_list.push_back(20);
    singly_list.push_back(30);
    PrintValues("SinglyLinkedList values", singly_list.to_vector());
    cout << "Contains 20: " << BoolText(singly_list.contains(20)) << endl << endl;

    PrintStructureInfo(DoublyLinkedList<int>::GetInfo());
    DoublyLinkedList<int> doubly_list;
    doubly_list.push_front(5);
    doubly_list.push_back(15);
    doubly_list.push_back(25);
    doubly_list.pop_front();
    PrintValues("DoublyLinkedList values", doubly_list.to_vector());
    cout << "Contains 25: " << BoolText(doubly_list.contains(25)) << endl << endl;

    PrintStructureInfo(Stack<int>::GetInfo());
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    PrintValues("Stack snapshot (bottom -> top)", stack.snapshot());
    cout << "Stack top: " << stack.top() << endl << endl;

    PrintStructureInfo(Queue<int>::GetInfo());
    Queue<int> queue;
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    queue.dequeue();
    PrintValues("Queue snapshot (front -> back)", queue.snapshot());
    cout << "Queue front: " << queue.front() << ", back: " << queue.back() << endl << endl;

    PrintStructureInfo(Deque<int>::GetInfo());
    Deque<int> deque;
    deque.push_front(10);
    deque.push_back(20);
    deque.push_front(5);
    PrintValues("Deque snapshot (front -> back)", deque.snapshot());
    cout << "Deque front: " << deque.front() << ", back: " << deque.back() << endl << endl;

    PrintTitle("Non-Linear Structures");

    PrintStructureInfo(HashTable<string, int>::GetInfo());
    HashTable<string, int> grades;
    grades.insert("Ali", 95);
    grades.insert("Lina", 88);
    grades.insert("Omar", 91);
    cout << "HashTable contains Lina: " << BoolText(grades.contains("Lina")) << endl;
    cout << "Omar grade: " << grades.at("Omar") << endl << endl;

    PrintStructureInfo(Graph::GetInfo());
    Graph graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 4);
    PrintValues("Graph BFS from 0", graph.bfs(0));
    PrintValues("Graph DFS from 0", graph.dfs(0));
    cout << endl;

    PrintTitle("Tree Implementations");

    PrintStructureInfo(GeneralTree<string>::GetInfo());
    GeneralTree<string> general_tree;
    auto  root_department = general_tree.set_root("Company");
    auto  engineering = general_tree.add_child(root_department, "Engineering");
    general_tree.add_child(root_department, "Sales");
    general_tree.add_child(engineering, "Backend");
    general_tree.add_child(engineering, "Frontend");
    PrintValues("GeneralTree preorder", general_tree.preorder());
    cout << endl;

    PrintStructureInfo(BinaryTree<string>::GetInfo());
    BinaryTree<string> binary_tree;
    auto  root = binary_tree.set_root("A");
    auto  left = binary_tree.insert_left(root, "B");
    auto  right = binary_tree.insert_right(root, "C");
    binary_tree.insert_left(left, "D");
    binary_tree.insert_right(left, "E");
    binary_tree.insert_left(right, "F");
    binary_tree.insert_right(right, "G");
    PrintValues("BinaryTree preorder", binary_tree.preorder());
    PrintValues("BinaryTree inorder", binary_tree.inorder());
    PrintValues("BinaryTree postorder", binary_tree.postorder());
    cout << endl;

    PrintStructureInfo(BinarySearchTree<int>::GetInfo());
    BinarySearchTree<int> bst;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        bst.insert(value);
    }
    bst.remove(70);
    PrintValues("BST inorder", bst.inorder());
    cout << "BST contains 60: " << BoolText(bst.contains(60)) << endl << endl;

    PrintStructureInfo(AVLTree<int>::GetInfo());
    AVLTree<int> avl;
    for (int value : {10, 20, 30, 40, 50, 25}) {
        avl.insert(value);
    }
    PrintValues("AVL inorder", avl.inorder());
    cout << "AVL contains 25: " << BoolText(avl.contains(25)) << endl << endl;

    PrintStructureInfo(HeapTree<int, less<int>>::GetInfo());
    HeapTree<int, less<int>> min_heap;
    for (int value : {8, 3, 10, 1, 6}) {
        min_heap.push(value);
    }
    PrintValues("Heap internal array", min_heap.as_array());
    cout << "Heap top priority: " << min_heap.top() << endl << endl;

    PrintStructureInfo(Trie::GetInfo());
    Trie trie;
    trie.insert("tree");
    trie.insert("trie");
    trie.insert("algorithm");
    cout << "Trie contains 'tree': " << BoolText(trie.contains("tree")) << endl;
    cout << "Trie starts with 'tri': " << BoolText(trie.starts_with("tri")) << endl << endl;

    PrintStructureInfo(SegmentTree::GetInfo());
    SegmentTree segment_tree({2, 1, 5, 3, 4});
    cout << "SegmentTree sum [1, 3]: " << segment_tree.range_sum(1, 3) << endl;
    segment_tree.update(2, 10);
    cout << "SegmentTree sum [1, 3] after update: " << segment_tree.range_sum(1, 3) << endl << endl;

    PrintStructureInfo(FenwickTree::GetInfo());
    FenwickTree fenwick({2, 1, 5, 3, 4});
    cout << "Fenwick prefix sum [0, 3]: " << fenwick.prefix_sum(3) << endl;
    fenwick.add(2, 5);
    cout << "Fenwick range sum [1, 3] after add: " << fenwick.range_sum(1, 3) << endl << endl;

    PrintStructureInfo(BTree<int, 2>::GetInfo());
    BTree<int, 2> btree;
    for (int value : {10, 20, 5, 6, 12, 30, 7, 17}) {
        btree.insert(value);
    }
    PrintValues("B-Tree inorder", btree.inorder());
    cout << "B-Tree contains 12: " << BoolText(btree.contains(12)) << endl << endl;

    PrintTitle("Additional Tree Families");
    for (const auto& tree_info : AdditionalTreeFamilies()) {
        PrintStructureInfo(tree_info);
    }

    cout << "Reference project is ready.\n";
        return 0;
}
