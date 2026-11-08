#pragma once
#include <memory>
#include "model/AVLTree.h"
#include "model/BST.h"
#include "model/BinaryTree.h"
#include "model/EventLog.h"
#include "model/MaxHeap.h"

// Ready-made model objects and event logs so the GUI (Person B) can render and animate
// BEFORE the Act algorithms exist. Nothing here calls an unimplemented algorithm.
namespace vh::sample {

// General binary tree, 7 nodes, values 5 / 12 7 / 3 9 4 8 (ids 1..7 in that order). Not ordered.
std::unique_ptr<BinaryTree> binaryTree();

// Balanced BST, keys 50 / 30 70 / 20 40 60 80 (ids 1..7 in that order).
std::unique_ptr<BST> bst();

// Same shape as bst() as an AVL tree with correct stored heights and sizes. All badges balanced.
std::unique_ptr<AVLTree> avlBalanced();

// AVL-typed chain 30 -> 20 -> 10 to the left (ids 1..3), correct heights/sizes. Root has balance factor +2 (LL case).
std::unique_ptr<AVLTree> avlLeftHeavy();

// Valid Max Heap, array {90,70,80,40,50,60,30}, heapSize 7.
std::unique_ptr<MaxHeap> heap();

// Mid Heap Sort state: array {60,50,30,40,70,80,90}, heapSize 4 (indices 4..6 are the sorted region).
std::unique_ptr<MaxHeap> heapWithSortedRegion();

// Event logs matching the samples above (ids/indices line up with them).
ModelEventLog bstSearchEvents();        // search for 60 in bst(): VISIT/COMPARE x3, DONE
ModelEventLog avlRotationEvents();      // fix avlLeftHeavy(): BALANCE_ALERT, ROTATE (LL), UPDATE_HEIGHT/SIZE, DONE
ModelEventLog heapExtractEvents();      // extractMax on heap(): EXTRACT_MAX, HEAP_SWAP, HEAP_SIZE_CHANGE, MARK_SORTED, heapify, DONE

} // namespace vh::sample
