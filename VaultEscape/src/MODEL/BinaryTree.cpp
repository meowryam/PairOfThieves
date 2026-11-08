#include "model/BinaryTree.h"
#include <algorithm>

namespace vh {

BinaryTree::~BinaryTree() { destroySubtree(root_); }

// ---------------------------------------------------------------- implemented structure code

TreeNode* BinaryTree::createNode(int value) { return new TreeNode(nextId_++, value); }

TreeNode* BinaryTree::setRoot(int value) {
    clear();
    root_ = createNode(value);
    size_ = 1;
    return root_;
}

TreeNode* BinaryTree::addLeft(TreeNode* parent, int value) {
    if (!parent || parent->left) return nullptr;
    TreeNode* n = createNode(value);
    linkChild(parent, n, Side::LEFT);
    ++size_;
    return n;
}

TreeNode* BinaryTree::addRight(TreeNode* parent, int value) {
    if (!parent || parent->right) return nullptr;
    TreeNode* n = createNode(value);
    linkChild(parent, n, Side::RIGHT);
    ++size_;
    return n;
}

void BinaryTree::adoptRoot(TreeNode* newRoot) {
    if (newRoot == root_) return;
    destroySubtree(root_);
    root_ = newRoot;
    if (root_) root_->parent = nullptr;
    size_ = countNodes(root_);
    nextId_ = maxId(root_) + 1;
}

void BinaryTree::clear() {
    destroySubtree(root_);
    root_ = nullptr;
    size_ = 0;
    nextId_ = 1;
}

static TreeNode* cloneNodes(const TreeNode* src, TreeNode* parent) {
    if (!src) return nullptr;
    TreeNode* n = new TreeNode(src->id, src->value);
    n->parent = parent;
    n->left = cloneNodes(src->left, n);
    n->right = cloneNodes(src->right, n);
    return n;
}

std::unique_ptr<BinaryTree> BinaryTree::clone() const {
    auto copy = std::make_unique<BinaryTree>();
    copy->root_ = cloneNodes(root_, nullptr);
    copy->size_ = size_;
    copy->nextId_ = nextId_;
    return copy;
}

TreeNode* BinaryTree::findById(NodeId id) const { return findNodeById(root_, id); }

// ---------------------------------------------------------------- Act 1 stubs (TODO Person A)

std::vector<NodeId> BinaryTree::preorderRec() const { return {}; }     // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::preorderIter() const { return {}; }    // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::inorderRec() const { return {}; }      // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::inorderIter() const { return {}; }     // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::postorderRec() const { return {}; }    // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::postorderIter() const { return {}; }   // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::levelOrderRec() const { return {}; }   // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::levelOrderIter() const { return {}; }  // TODO(Person A - Act 1)

bool BinaryTree::buildFromPreIn(const std::vector<int>&, const std::vector<int>&) { return false; }   // TODO(Person A - Act 1)
bool BinaryTree::buildFromPostIn(const std::vector<int>&, const std::vector<int>&) { return false; }  // TODO(Person A - Act 1)

int BinaryTree::height(const TreeNode*) { return 0; }                        // TODO(Person A - Act 1)
int BinaryTree::diameter() const { return 0; }                               // TODO(Person A - Act 1)
TreeNode* BinaryTree::lca(NodeId, NodeId) const { return nullptr; }          // TODO(Person A - Act 1)
std::vector<NodeId> BinaryTree::pathTo(NodeId) const { return {}; }          // TODO(Person A - Act 1)
void BinaryTree::mirror() {}                                                 // TODO(Person A - Act 1)
bool BinaryTree::isSameTree(const BinaryTree&) const { return false; }       // TODO(Person A - Act 1)
bool BinaryTree::isSymmetric() const { return false; }                       // TODO(Person A - Act 1)

} // namespace vh
