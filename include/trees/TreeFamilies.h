#pragma once

#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

inline vector<StructureInfo> AdditionalTreeFamilies() {
    return {
        {"Red-Black Tree",
         "Tree",
         "Self-balancing BST that uses node colors and rotation rules to keep height logarithmic.",
         "Ordered by key value like a BST.",
         "Linked binary nodes with an extra color bit.",
         "Grows and rebalances using recoloring and rotations.",
         "Usually unique keys in search-tree use cases.",
         "Ordered maps and sets in many standard libraries.",
         {"O(log n)", "O(log n)", "O(log n)", "O(log n)", "O(n)",
          "Usually slightly less rigidly balanced than AVL, but often cheaper to update."},
         {"Excellent general-purpose balanced search tree.", "Widely used in production libraries."},
         {"Balancing rules are more subtle than a plain BST.", "Implementation is more involved than AVL insert only."}},

        {"Splay Tree",
         "Tree",
         "Self-adjusting BST that rotates recently accessed nodes toward the root.",
         "Ordered by key value like a BST.",
         "Linked binary nodes.",
         "Grows normally, but every access may restructure the tree.",
         "Typically unique keys in set-style usage.",
         "Workloads with temporal locality where recently used keys are likely to be reused.",
         {"Amortized O(log n)", "Amortized O(log n)", "Amortized O(log n)", "Amortized O(log n)", "O(n)",
          "Single operations can still be linear in the worst case."},
         {"Simple node metadata compared with AVL or Red-Black.", "Frequently accessed items move near the root."},
         {"Tree shape changes on search.", "Worst-case single access is not bounded by O(log n)."}},

        {"B+ Tree",
         "Tree",
         "Variant of B-Tree where all actual records are stored at the leaves and internal nodes act as guides.",
         "Ordered by key value across leaf pages.",
         "Multi-way nodes plus linked leaves.",
         "Grows by splitting full pages and preserving leaf-level order.",
         "Depends on the underlying record model.",
         "Database indexes and file systems with heavy range scanning.",
         {"O(log n)", "O(log n)", "O(log n)", "O(log n)", "O(n)",
          "Leaf chaining makes sequential range scans especially efficient."},
         {"Great for disk-based indexes.", "Excellent range-query performance."},
         {"More moving parts than a BST.", "Implementation details are storage-system heavy."}},

        {"KD-Tree",
         "Tree",
         "Binary space-partitioning tree for points in k-dimensional space.",
         "Ordered by alternating dimensions rather than a single scalar key.",
         "Linked binary nodes that split space by axis.",
         "Grows one point at a time or from recursive partitioning.",
         "Identical points may require special policies.",
         "Nearest-neighbor search, geometric lookup, and spatial partitioning.",
         {"O(log n) average", "O(log n) average, O(n) worst", "O(log n) average", "Commonly O(log n) average", "O(n)",
          "Performance drops in high dimensions."},
         {"Useful for geometric queries.", "Natural fit for multi-dimensional points."},
         {"Not ideal for very high-dimensional data.", "Balancing and splitting policy matter a lot."}},

        {"Quad Tree / Octree",
         "Tree",
         "Spatial trees that recursively divide 2D space into four regions or 3D space into eight regions.",
         "Ordered by space subdivision, not by scalar key comparison.",
         "Hierarchical region nodes.",
         "Grows by subdividing regions that become crowded.",
         "Depends on stored objects.",
         "Game maps, image processing, collision detection, and spatial indexing.",
         {"O(log n) average", "O(log n) average", "O(log n) average", "O(log n) average", "O(n)",
          "Complexity depends heavily on spatial distribution."},
         {"Efficient for sparse spatial data.", "Prunes large empty regions well."},
         {"Can become imbalanced with clustered data.", "Implementation is domain specific."}}
    };
}

}  // namespace ds
