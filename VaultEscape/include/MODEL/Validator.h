#pragma once
#include <string>
#include <vector>

namespace vh {

class BinaryTree;
class BST;
class AVLTree;
class MaxHeap;

struct ValidationResult {
    bool ok = true;
    std::vector<std::string> errors;        // one human-readable line per violated invariant
    void fail(const std::string& message) { ok = false; errors.push_back(message); }
    explicit operator bool() const { return ok; }
};

// Invariant checks. Run in debug mode after every operation and in every unit test.
// Status: interface only. Each body is a stub that currently returns ok (TODO), owned by the Act owner.
class Validator {
public:
    // TODO(Person A - Act 1): parent links consistent; no cycles / shared nodes (reachable count == size()).
    static ValidationResult validate(const BinaryTree& tree);
    // TODO(Person B - Act 2): everything above + BST ordering (left < node < right), no duplicate keys.
    static ValidationResult validate(const BST& tree);
    // TODO(Person A - Act 3): everything above + stored height == recomputed, stored size == recomputed,
    //                         |balanceFactor| <= 1 for every node.
    static ValidationResult validate(const AVLTree& tree);
    // TODO(Person B - Act 4): 0 <= heapSize <= size(); every active parent >= its existing children;
    //                         sorted region ascending and every sorted value >= every active value.
    static ValidationResult validate(const MaxHeap& heap);
};

} // namespace vh
