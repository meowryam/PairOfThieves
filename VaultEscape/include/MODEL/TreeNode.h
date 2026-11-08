#pragma once
#include <string>
#include "model/Types.h"

namespace vh {

// Act 1 node. `value` is the treasure value shown in the room.
// Ownership: the tree object that created a node owns it and frees it (see destroySubtree).
struct TreeNode {
    NodeId id = INVALID_ID;
    int value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode* parent = nullptr;        // kept consistent; Validator checks it

    TreeNode() = default;
    TreeNode(NodeId id_, int value_) : id(id_), value(value_) {}
    virtual ~TreeNode() = default;
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;
};

// Act 2 node. `key` is the ordering field. For BST/AVL nodes created by createNode(key), value == key.
struct BSTNode : TreeNode {
    int key = 0;
    std::string treasure;              // optional display name of the treasure

    BSTNode() = default;
    BSTNode(NodeId id_, int key_) : TreeNode(id_, key_), key(key_) {}
};

// Act 3 node. Convention: leaf height = 1, empty subtree height = 0; leaf size = 1.
struct AVLNode : BSTNode {
    int height = 1;
    int size = 1;

    AVLNode() = default;
    AVLNode(NodeId id_, int key_) : BSTNode(id_, key_) {}
};

// ---- Small shared helpers (implemented; iterative, safe for 10,000-deep chains) ----
void linkChild(TreeNode* parent, TreeNode* child, Side side);  // sets parent->left/right and child->parent
void destroySubtree(TreeNode* node);                           // deletes node and all descendants
int  countNodes(const TreeNode* node);                         // nodes in subtree (0 for nullptr)
NodeId maxId(const TreeNode* node);                            // largest id in subtree (0 for nullptr)
TreeNode* findNodeById(TreeNode* root, NodeId id);             // nullptr if absent

} // namespace vh
