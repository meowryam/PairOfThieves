#include "model/LevelManager.h"
#include "model/AVLTree.h"
#include "model/BST.h"
#include "model/BinaryTree.h"

namespace vh {

void LevelManager::addLevel(const LevelDef& def) { levels_.push_back(def); }

const LevelDef* LevelManager::findLevel(const std::string& id) const {
    for (const LevelDef& d : levels_)
        if (d.id == id) return &d;
    return nullptr;
}

const LevelDef* LevelManager::currentLevel() const {
    if (current_ < 0 || current_ >= levelCount()) return nullptr;
    return &levels_[current_];
}

bool LevelManager::setCurrent(const std::string& id) {
    for (int i = 0; i < levelCount(); ++i) {
        if (levels_[i].id == id) { current_ = i; return true; }
    }
    return false;
}

bool LevelManager::advance() {
    if (current_ + 1 >= levelCount()) return false;
    ++current_;
    return true;
}

LevelStatus LevelManager::evaluate(const ScoreSystem& score, bool objectiveComplete) {
    if (score.alarmFull()) return LevelStatus::FAILED;
    return objectiveComplete ? LevelStatus::WON : LevelStatus::IN_PROGRESS;
}

// ---------------------------------------------------------------- stubs (TODO)

bool LevelManager::loadFromFile(const std::string&) { return false; }                               // TODO
std::unique_ptr<BinaryTree> LevelManager::generateBinaryTree(const LevelDef&) const { return nullptr; }  // TODO
std::unique_ptr<BST> LevelManager::generateBST(const LevelDef&) const { return nullptr; }                // TODO
std::unique_ptr<AVLTree> LevelManager::generateAVL(const LevelDef&) const { return nullptr; }            // TODO
std::vector<int> LevelManager::generateHeapArray(const LevelDef&) const { return {}; }                   // TODO
int LevelManager::computeOptimalSteps(const LevelDef&) const { return 0; }                               // TODO

} // namespace vh
