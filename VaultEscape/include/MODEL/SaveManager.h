#pragma once
#include <string>
#include <vector>

namespace vh {

struct TreeNode;
class BinaryTree;
class BST;
class AVLTree;
class MaxHeap;

struct LevelProgress {
    std::string levelId;
    int stars = 0;
    bool completed = false;
};

// Everything the save file stores.
struct SaveData {
    std::vector<LevelProgress> campaign;
    std::string endlessKind;            // "BINARY" | "BST" | "AVL" | "MAX_HEAP" (empty = no endless run saved)
    std::string endlessState;           // serializeTree(...) or serializeHeap(...) text
    unsigned endlessSeed = 0;
};

// Text formats (agreed):
//   tree: preorder with '#' for null, space separated, e.g. "50 30 # # 70 60 # # #"
//         (BST/AVL store the key; the AVL height and size are NOT stored)
//   heap: "<heapSize>: v0 v1 v2 ..."   (underlying array plus active heap size)
// Status: interface only; every body is a stub (TODO, shared by both people).
class SaveManager {
public:
    static std::string serializeTree(const TreeNode* root);                   // an empty tree serialises to "#"
    static bool loadBinaryTree(const std::string& text, BinaryTree& out);     // false on malformed text; `out` unchanged
    static bool loadBST(const std::string& text, BST& out);                   // false on malformed text; `out` unchanged
    // loadAVL: build the shape, recompute heights and sizes, run Validator; false if invalid.
    static bool loadAVL(const std::string& text, AVLTree& out);

    static std::string serializeHeap(const MaxHeap& heap);
    static bool loadHeap(const std::string& text, MaxHeap& out);

    static bool saveToFile(const std::string& path, const SaveData& data);    // false on I/O failure
    static bool loadFromFile(const std::string& path, SaveData& out);         // false on I/O failure or bad data
};

} // namespace vh
