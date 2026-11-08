#pragma once
#include <memory>
#include <string>
#include <vector>
#include "model/Types.h"
#include "model/ScoreSystem.h"

namespace vh {

class BinaryTree;
class BST;
class AVLTree;

// One level, exactly as described in data/levels/levels.json. Optimal steps are NEVER stored
// here: they are computed by the model (computeOptimalSteps).
//
// `type` names (one per campaign level):
//   Act 1: traversal, reconstruction, height_diameter, lca_path, mirror
//   Act 2: bst_search, bst_insert, bst_delete, bst_range, bst_boss
//   Act 3: avl_badges, avl_single, avl_double, avl_auto, avl_kth
//   Act 4: heap_build, heap_repair, heap_extract, heap_race, heap_boss
// `generator` names: random, sorted, reverse, skewed, heap, duplicates, explicit.
// If `values` is non-empty the structure is built from it; otherwise it is generated from
// (seed, nodeCount, generator) so results are reproducible.
struct LevelDef {
    std::string id;                     // "1.1" ... "4.5"
    int act = 1;
    int number = 1;
    std::string title;
    std::string mission;
    std::string topic;                 // concept taught, e.g. "Traversals"
    std::string type;
    TreeKind kind = TreeKind::BINARY;
    unsigned seed = 0;
    int nodeCount = 0;
    std::string generator = "random";
    std::vector<int> values;
    // Optional per-type parameters (0 / empty when unused):
    std::string traversal;              // 1.1: preorder | inorder | postorder | levelorder
    int targetKey = 0;                  // 2.1 search target
    int rangeLo = 0, rangeHi = 0;       // 2.4 range query
    int k = 0;                          // 3.5 k-th most valuable
};

enum class LevelStatus { IN_PROGRESS, WON, FAILED };

// Holds the level list and the current level, builds structures for a level, and decides win/lose.
// Status: list handling and status evaluation are implemented. JSON loading, generation and optimal-step
// computation are stubs (TODO) - see the individual comments.
class LevelManager {
public:
    // ---- Level list (implemented) ----
    void addLevel(const LevelDef& def);                 // lets the GUI/tests register levels without JSON
    const std::vector<LevelDef>& levels() const { return levels_; }
    int levelCount() const { return static_cast<int>(levels_.size()); }
    const LevelDef* findLevel(const std::string& id) const;   // nullptr if absent
    const LevelDef* currentLevel() const;               // nullptr if none selected
    int currentIndex() const { return current_; }
    bool setCurrent(const std::string& id);             // false if id unknown
    bool advance();                                     // move to the next level in file order; false if already last

    // ---- Win / lose (implemented) ----
    // The per-level objective check (click sequence correct, tree equals target, ...) is done by the
    // level logic and passed in as `objectiveComplete`. Failure always wins: full alarm = FAILED.
    static LevelStatus evaluate(const ScoreSystem& score, bool objectiveComplete);

    // ---- To do ----
    // TODO: parse the JSON file (pick one JSON library together with Person B, e.g. nlohmann/json),
    //       fill levels_, return false on a missing file or malformed level.
    bool loadFromFile(const std::string& path);
    // TODO: seeded generation (same def => same structure). Return nullptr if def.kind does not match.
    std::unique_ptr<BinaryTree> generateBinaryTree(const LevelDef& def) const;
    std::unique_ptr<BST> generateBST(const LevelDef& def) const;
    std::unique_ptr<AVLTree> generateAVL(const LevelDef& def) const;
    std::vector<int> generateHeapArray(const LevelDef& def) const;
    // TODO: optimal steps computed by running the model on the generated structure.
    int computeOptimalSteps(const LevelDef& def) const;

private:
    std::vector<LevelDef> levels_;
    int current_ = -1;
};

} // namespace vh
