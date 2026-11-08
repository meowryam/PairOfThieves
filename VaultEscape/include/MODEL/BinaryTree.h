#pragma once
#include <memory>
#include <vector>
#include "model/ModelBase.h"
#include "model/TreeNode.h"

namespace vh {

// General binary tree (Act 1): arbitrary values, no ordering.
//
// Conventions (agree with Person B):
//   * height counts NODES: empty = 0, leaf = 1 (same as AVLNode.height).
//   * diameter and path lengths count EDGES.
//   * Reconstruction assumes all values are distinct.
//   * isSameTree compares shape and values; node ids are ignored.
//
// Status of this file: structure-building functions are implemented; every function in the
// "Act 1 algorithms" block is a stub (TODO Person A) that currently returns an empty/neutral value.
class BinaryTree : public ModelBase {
public:
    BinaryTree() = default;
    ~BinaryTree() override;
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    // ---- Structure building and access (implemented) ----
    TreeNode* createNode(int value);                    // new unlinked node with a fresh unique id (tree owns it)
    TreeNode* setRoot(int value);                       // clear tree, make a single root; returns it
    TreeNode* addLeft(TreeNode* parent, int value);     // nullptr if parent null or slot occupied
    TreeNode* addRight(TreeNode* parent, int value);    // same
    void adoptRoot(TreeNode* newRoot);                  // free old tree, take ownership of a fully linked tree
    void clear();
    std::unique_ptr<BinaryTree> clone() const;          // deep copy, ids preserved

    TreeNode* root() const { return root_; }
    int size() const { return size_; }
    bool empty() const { return root_ == nullptr; }
    TreeNode* findById(NodeId id) const;                // nullptr if absent

    // ---- Act 1 algorithms (TODO Person A) ----
    // Traversals return node ids. Recursive and iterative versions must agree.
    // Events: one VISIT per node in visiting order, then DONE.
    std::vector<NodeId> preorderRec() const;
    std::vector<NodeId> preorderIter() const;
    std::vector<NodeId> inorderRec() const;
    std::vector<NodeId> inorderIter() const;
    std::vector<NodeId> postorderRec() const;
    std::vector<NodeId> postorderIter() const;
    std::vector<NodeId> levelOrderRec() const;
    std::vector<NodeId> levelOrderIter() const;

    // Reconstruction: replaces this tree on success. Returns false on invalid/mismatched input.
    // Inputs are node VALUES (distinct). Events: none (DONE only).
    bool buildFromPreIn(const std::vector<int>& pre, const std::vector<int>& in);
    bool buildFromPostIn(const std::vector<int>& post, const std::vector<int>& in);

    static int height(const TreeNode* node);            // nodes convention, height(nullptr) == 0
    int diameter() const;                               // longest path between any two nodes, in edges; 0 if empty
    TreeNode* lca(NodeId a, NodeId b) const;            // nullptr if either id is absent
    std::vector<NodeId> pathTo(NodeId target) const;    // root ... target; empty if absent
    void mirror();                                      // swap children recursively; events: DONE only
    bool isSameTree(const BinaryTree& other) const;     // shape + values
    bool isSymmetric() const;                           // tree is a mirror image of itself

private:
    TreeNode* root_ = nullptr;
    int size_ = 0;
    NodeId nextId_ = 1;
};

} // namespace vh
