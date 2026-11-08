#include "model/TreeNode.h"
#include <vector>

namespace vh {

void linkChild(TreeNode* parent, TreeNode* child, Side side) {
    if (!parent) return;
    if (side == Side::LEFT) parent->left = child;
    else if (side == Side::RIGHT) parent->right = child;
    if (child) child->parent = parent;
}

void destroySubtree(TreeNode* node) {
    std::vector<TreeNode*> stack;
    if (node) stack.push_back(node);
    while (!stack.empty()) {
        TreeNode* n = stack.back();
        stack.pop_back();
        if (n->left) stack.push_back(n->left);
        if (n->right) stack.push_back(n->right);
        delete n;
    }
}

int countNodes(const TreeNode* node) {
    int count = 0;
    std::vector<const TreeNode*> stack;
    if (node) stack.push_back(node);
    while (!stack.empty()) {
        const TreeNode* n = stack.back();
        stack.pop_back();
        ++count;
        if (n->left) stack.push_back(n->left);
        if (n->right) stack.push_back(n->right);
    }
    return count;
}

NodeId maxId(const TreeNode* node) {
    NodeId best = 0;
    std::vector<const TreeNode*> stack;
    if (node) stack.push_back(node);
    while (!stack.empty()) {
        const TreeNode* n = stack.back();
        stack.pop_back();
        if (n->id > best) best = n->id;
        if (n->left) stack.push_back(n->left);
        if (n->right) stack.push_back(n->right);
    }
    return best;
}

TreeNode* findNodeById(TreeNode* root, NodeId id) {
    std::vector<TreeNode*> stack;
    if (root) stack.push_back(root);
    while (!stack.empty()) {
        TreeNode* n = stack.back();
        stack.pop_back();
        if (n->id == id) return n;
        if (n->left) stack.push_back(n->left);
        if (n->right) stack.push_back(n->right);
    }
    return nullptr;
}

} // namespace vh
