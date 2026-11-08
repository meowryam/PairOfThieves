#include "model/SaveManager.h"

namespace vh {

std::string SaveManager::serializeTree(const TreeNode*) { return ""; }             // TODO
bool SaveManager::loadBinaryTree(const std::string&, BinaryTree&) { return false; } // TODO
bool SaveManager::loadBST(const std::string&, BST&) { return false; }               // TODO
bool SaveManager::loadAVL(const std::string&, AVLTree&) { return false; }           // TODO
std::string SaveManager::serializeHeap(const MaxHeap&) { return ""; }               // TODO
bool SaveManager::loadHeap(const std::string&, MaxHeap&) { return false; }          // TODO
bool SaveManager::saveToFile(const std::string&, const SaveData&) { return false; } // TODO
bool SaveManager::loadFromFile(const std::string&, SaveData&) { return false; }     // TODO

} // namespace vh
