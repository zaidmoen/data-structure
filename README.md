# Data Structures in C++

An educational C++ reference project that implements core data structures with clean header-only examples, complexity notes, and a single demo program that shows how each structure behaves.

## Overview

This repository is designed as a compact learning resource for students and developers who want to study classic data structures in one place. Each structure exposes:

- A focused implementation in `include/`
- A `GetInfo()` description with use cases, strengths, weaknesses, and complexity notes
- A practical example in `main.cpp`

The project currently covers linear structures, non-linear structures, and multiple tree variants.

## Implemented Structures

### Linear Structures

- Dynamic Array
- Singly Linked List
- Doubly Linked List
- Stack
- Queue
- Deque

### Non-Linear Structures

- Hash Table
- Graph

### Tree Structures

- General Tree
- Binary Tree
- Binary Search Tree
- AVL Tree
- Heap
- Trie
- Segment Tree
- Fenwick Tree
- B-Tree

### Additional Tree Families Included as Reference Notes

- Red-Black Tree
- Splay Tree
- B+ Tree
- KD-Tree
- Quad Tree / Octree

## Project Structure

```text
.
|-- include/
|   |-- common/
|   |   `-- StructureInfo.h
|   |-- linear/
|   |-- nonlinear/
|   `-- trees/
`-- main.cpp
```

## Build and Run

### GCC / MinGW

```bash
g++ -std=c++17 -I. main.cpp -o data-structures
./data-structures
```

### MSVC

```powershell
cl /EHsc /std:c++17 /I. main.cpp
.\main.exe
```

## What the Demo Shows

When you run `main.cpp`, the program:

- Prints a short profile for each structure
- Demonstrates common operations such as insert, remove, traversal, and search
- Shows example outputs to help compare behavior between structures

## Why This Repository Is Useful

- Good for learning and revision
- Easy to extend with new structures
- Keeps theory close to code
- Useful as a classroom, portfolio, or self-study reference

## Notes

- The implementations are written for clarity and learning value.
- Some advanced production concerns are intentionally simplified to keep the code approachable.

## Future Improvements

- Add unit tests
- Add more graph algorithms
- Add deletion and balancing extensions for more tree variants
- Add benchmark comparisons between structures

## License

No license file is currently included in this repository.
