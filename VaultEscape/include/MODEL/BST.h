#pragma once
#include <vector>
#include "model/ModelBase.h"
#include "model/TreeNode.h"

namespace vh {

// Binary Search Tree (Act 2). Smaller keys left, larger keys right. Duplicates are rejected.
// AVLTree extends this class and overrides the virtuals.
//
// Status: structure/ownership code is implemented; every function in the "Act 2 algorithms"
// block is a stub (TODO Person B) that currently returns a neutral value.
class BST : public ModelBase {
public:
    BST() = default;
    ~BST() override;
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    // ---- Structure and access (implemented) ----
    virtual BSTNode* createNode(int key);               // new unlinked node, fresh id (AVLTree returns an AVLNode)
    virtual void adoptRoot(TreeNode* newRoot);          // free old tree, take ownership of a fully linked tree
    void clear();

    BSTNode* root() const { return root_; }
    int size() const { return size_; }                  // number of keys; operations must keep it up to date
    bool empty() const { return root_ == nullptr; }

    // ---- Act 2 algorithms (TODO Person B) ----
    // insert: false (and no change) if key already exists - emit a DONE event whose text says "duplicate".
    //         Events: VISIT/COMPARE along the path, INSERT, DONE.
    virtual bool insert(int key);
    // search: nullptr if absent. Events: VISIT + COMPARE per room on the path, DONE.
    BSTNode* search(int key) const;
    // remove (the spec's delete): false if key is absent.
    //         Events: VISIT/COMPARE to find it; leaf -> UNLINK; one child -> UNLINK/bypass;
    //         two children -> HIGHLIGHT successor, SWAP_VALUE, then delete the successor; DONE.
    virtual bool remove(int key);
    // findMin/findMax of the subtree rooted at `from` (nullptr = whole tree). nullptr if empty.
    BSTNode* findMin(BSTNode* from = nullptr) const;
    BSTNode* findMax(BSTNode* from = nullptr) const;
    BSTNode* successor(const BSTNode* node) const;      // next larger key, nullptr if none
    BSTNode* predecessor(const BSTNode* node) const;    // next smaller key, nullptr if none
    // rangeQuery: keys in [lo, hi] ascending. Emits HIGHLIGHT_SUBTREE (SKIPPED) for pruned subtrees.
    std::vector<int> rangeQuery(int lo, int hi) const;
    BSTNode* kthSmallest(int k) const;                  // 1-based, O(n) inorder counter; nullptr if k out of range
    BSTNode* lcaBST(int a, int b) const;                // uses ordering; nullptr if a key is absent
    int height() const;                                 // nodes convention (empty 0, leaf 1); needed by level 2.5 and benchmarks

    static BSTNode* asBST(TreeNode* n) { return static_cast<BSTNode*>(n); }

protected:
    BSTNode* root_ = nullptr;
    int size_ = 0;
    NodeId nextId_ = 1;
};

} // namespace vh
