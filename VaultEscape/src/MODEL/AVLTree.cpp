#include "model/AVLTree.h"

namespace vh {

BSTNode* AVLTree::createNode(int key) { return new AVLNode(nextId_++, key); }

void AVLTree::adoptRoot(TreeNode* newRoot) {
    BST::adoptRoot(newRoot);
    // TODO(Person A - Act 3): recompute height and size of every node (loaded trees do not store them).
}

// ---------------------------------------------------------------- Act 3 stubs (TODO Person A)

bool AVLTree::insert(int) { return false; }                              // TODO(Person A - Act 3)
bool AVLTree::remove(int) { return false; }                              // TODO(Person A - Act 3)
AVLNode* AVLTree::rotateLeft(AVLNode*) { return nullptr; }               // TODO(Person A - Act 3)
AVLNode* AVLTree::rotateRight(AVLNode*) { return nullptr; }              // TODO(Person A - Act 3)
AVLNode* AVLTree::rebalance(AVLNode*) { return nullptr; }                // TODO(Person A - Act 3)
int AVLTree::nodeHeight(const AVLNode*) const { return 0; }              // TODO(Person A - Act 3)
int AVLTree::subtreeSize(const AVLNode*) const { return 0; }             // TODO(Person A - Act 3)
int AVLTree::balanceFactor(const AVLNode*) const { return 0; }           // TODO(Person A - Act 3)
AVLNode* AVLTree::kth(int) const { return nullptr; }                     // TODO(Person A - Act 3)
int AVLTree::rank(int) const { return 0; }                               // TODO(Person A - Act 3)
int AVLTree::countInRange(int, int) const { return 0; }                  // TODO(Person A - Act 3)
bool AVLTree::isBalanced() const { return true; }                        // TODO(Person A - Act 3)

} // namespace vh
