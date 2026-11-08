#pragma once
#include <string>
#include <vector>
#include "model/ModelBase.h"

namespace vh {

// Array-based Max Heap and Heap Sort (Act 4). No node objects: the tree view is derived from
// index arithmetic (zero-based). The array has two regions:
//     [0, heapSize)        active heap
//     [heapSize, size())   sorted region (extracted maxima, ascending)
//
// Status: representation, index helpers and state access are implemented; every function in the
// "Act 4 algorithms" block is a stub (TODO Person B) that currently does nothing / returns 0.
// Counters: comparisons and swaps go into stats() so benchmarks work with events disabled.
class MaxHeap : public ModelBase {
public:
    MaxHeap() = default;
    explicit MaxHeap(const std::vector<int>& values) { setState(values, static_cast<int>(values.size())); }

    // ---- Index arithmetic (implemented). Do not call parentIndex(0): the root has no parent. ----
    static int parentIndex(int i) { return (i - 1) / 2; }
    static int leftIndex(int i) { return 2 * i + 1; }
    static int rightIndex(int i) { return 2 * i + 2; }

    // ---- State access (implemented) ----
    const std::vector<int>& array() const { return data_; }
    int size() const { return static_cast<int>(data_.size()); }   // total array length
    int heapSize() const { return heapSize_; }                    // active heap size
    bool empty() const { return heapSize_ == 0; }
    // Replace the array and active size WITHOUT heapifying (used by levels, undo snapshots, load).
    // heapSize is clamped to [0, a.size()]. Emits no events.
    void setState(const std::vector<int>& a, int heapSize);

    // ---- Act 4 algorithms (TODO Person B) ----
    // Swap two array cells. Emits HEAP_SWAP(indexA, indexB, old/new values, reason); stats().swaps++.
    void swapElements(int i, int j, const std::string& reason = "");
    // Bottom-up O(n) construction. The array overload loads `a` first. Heap size becomes the array length.
    // Events: HEAP_BUILD, then per sift: HEAPIFY_START, HEAP_SWAPs, HEAPIFY_DONE; finally DONE.
    void buildMaxHeap(const std::vector<int>& a);
    void buildMaxHeap();                                // build on the current array
    // Move the element at i down inside the first `heapSize` cells until the heap property holds.
    void siftDown(int i, int heapSize);
    void heapify(int i = 0);                            // siftDown(i, heapSize())
    void siftUp(int i);                                 // move the element at i up
    void insert(int value);                             // append, siftUp; heap size + 1
    // extractMax: remove and return the root. Throws std::out_of_range if the heap is empty.
    // Events: EXTRACT_MAX, HEAP_SWAP (root <-> last active), HEAP_SIZE_CHANGE, MARK_SORTED,
    //         HEAPIFY_START/HEAP_SWAPs/HEAPIFY_DONE, DONE. The value stays in the array's sorted region.
    int extractMax();
    // Heap Sort, in place, ascending: build, then repeat extractMax steps until heapSize == 0.
    // Ends with HEAP_SORT_COMPLETE (array = sorted result) and DONE.
    void heapSort();
    void heapSort(const std::vector<int>& a);           // loads `a`, then heapSort()
    bool isMaxHeap() const;                             // property holds on the ACTIVE region only

private:
    std::vector<int> data_;
    int heapSize_ = 0;
};

} // namespace vh
