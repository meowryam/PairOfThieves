#pragma once
#include "model/BST.h"

namespace vh {

// AVL tree (Act 3), extends BST. Stored per node: height (leaf = 1) and subtree size (leaf = 1).
// balanceFactor(node) = height(left) - height(right).
//
// Status: createNode and adoptRoot are wired; everything in the "Act 3 algorithms" block is a
// stub (TODO Person A) that currently returns a neutral value.
// Note: BST::size() is the number of keys; the per-node size is read with subtreeSize().
class AVLTree : public BST {
public:
    AVLTree() = default;

    // ---- Structure (wired) ----
    BSTNode* createNode(int key) override;              // returns an AVLNode
    void adoptRoot(TreeNode* newRoot) override;         // TODO(Person A): recompute heights and sizes after adopting

    // ---- Act 3 algorithms (TODO Person A) ----
    // insert/remove: BST insert/delete, then rebalance while returning up the path.
    //   Events: as BST, plus UPDATE_HEIGHT, UPDATE_SIZE, BALANCE_ALERT, ROTATE; DONE.
    bool insert(int key) override;
    bool remove(int key) override;

    // Primitive rotations: return the new root of the rotated subtree. Update height and size of the
    // two moved nodes. Emit one ROTATE (+ UPDATE_HEIGHT / UPDATE_SIZE). Increment stats().rotations.
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    // rebalance: pick LL / RR / LR / RL from the balance factors, rotate, return the new subtree root.
    AVLNode* rebalance(AVLNode* node);

    int nodeHeight(const AVLNode* node) const;          // 0 for nullptr
    int subtreeSize(const AVLNode* node) const;         // 0 for nullptr
    int balanceFactor(const AVLNode* node) const;       // height(left) - height(right); 0 for nullptr

    AVLNode* kth(int k) const;                          // k-th smallest (1-based) in O(log n); nullptr if out of range
    int rank(int key) const;                            // number of keys <= key
    int countInRange(int lo, int hi) const;             // rank(hi) - rank(lo - 1)
    bool isBalanced() const;                            // every node has |balanceFactor| <= 1

    AVLNode* avlRoot() const { return static_cast<AVLNode*>(root_); }
    static AVLNode* asAVL(TreeNode* n) { return static_cast<AVLNode*>(n); }
};

} // namespace vh
