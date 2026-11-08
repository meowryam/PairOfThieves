#include "model/BST.h"

namespace vh {

BST::~BST() { destroySubtree(root_); }

// ---------------------------------------------------------------- implemented structure code

BSTNode* BST::createNode(int key) { return new BSTNode(nextId_++, key); }

void BST::adoptRoot(TreeNode* newRoot) {
    if (newRoot == root_) return;
    destroySubtree(root_);
    root_ = static_cast<BSTNode*>(newRoot);
    if (root_) root_->parent = nullptr;
    size_ = countNodes(root_);
    nextId_ = maxId(root_) + 1;
}

void BST::clear() {
    destroySubtree(root_);
    root_ = nullptr;
    size_ = 0;
    nextId_ = 1;
}

// ---------------------------------------------------------------- Act 2 stubs (TODO Person B)

bool BST::insert(int) { return false; }                                  // TODO(Person B - Act 2)
BSTNode* BST::search(int) const { return nullptr; }                      // TODO(Person B - Act 2)
bool BST::remove(int) { return false; }                                  // TODO(Person B - Act 2)
BSTNode* BST::findMin(BSTNode*) const { return nullptr; }                // TODO(Person B - Act 2)
BSTNode* BST::findMax(BSTNode*) const { return nullptr; }                // TODO(Person B - Act 2)
BSTNode* BST::successor(const BSTNode*) const { return nullptr; }        // TODO(Person B - Act 2)
BSTNode* BST::predecessor(const BSTNode*) const { return nullptr; }      // TODO(Person B - Act 2)
std::vector<int> BST::rangeQuery(int, int) const { return {}; }          // TODO(Person B - Act 2)
BSTNode* BST::kthSmallest(int) const { return nullptr; }                 // TODO(Person B - Act 2)
BSTNode* BST::lcaBST(int, int) const { return nullptr; }                 // TODO(Person B - Act 2)
int BST::height() const { return 0; }                                    // TODO(Person B - Act 2)

} // namespace vh
