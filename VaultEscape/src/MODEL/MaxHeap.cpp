#include "model/MaxHeap.h"
#include <algorithm>

namespace vh {

// ---------------------------------------------------------------- implemented

void MaxHeap::setState(const std::vector<int>& a, int heapSize) {
    data_ = a;
    const int n = static_cast<int>(a.size());
    heapSize_ = std::max(0, std::min(heapSize, n));
}

// ---------------------------------------------------------------- Act 4 stubs (TODO Person B)

void MaxHeap::swapElements(int, int, const std::string&) {}              // TODO(Person B - Act 4)
void MaxHeap::buildMaxHeap(const std::vector<int>&) {}                   // TODO(Person B - Act 4)
void MaxHeap::buildMaxHeap() {}                                          // TODO(Person B - Act 4)
void MaxHeap::siftDown(int, int) {}                                      // TODO(Person B - Act 4)
void MaxHeap::heapify(int) {}                                            // TODO(Person B - Act 4)
void MaxHeap::siftUp(int) {}                                             // TODO(Person B - Act 4)
void MaxHeap::insert(int) {}                                             // TODO(Person B - Act 4)
int MaxHeap::extractMax() { return 0; }                                  // TODO(Person B - Act 4)
void MaxHeap::heapSort() {}                                              // TODO(Person B - Act 4)
void MaxHeap::heapSort(const std::vector<int>&) {}                       // TODO(Person B - Act 4)
bool MaxHeap::isMaxHeap() const { return true; }                         // TODO(Person B - Act 4)

} // namespace vh
