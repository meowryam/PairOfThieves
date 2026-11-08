#pragma once
#include <string>
#include <vector>
#include "model/Types.h"

namespace vh {

enum class EventType {
    VISIT, COMPARE, INSERT, UNLINK, SWAP_VALUE, ROTATE,
    UPDATE_HEIGHT, UPDATE_SIZE, BALANCE_ALERT, HIGHLIGHT_SUBTREE,
    HEAP_BUILD, HEAP_SWAP, HEAPIFY_START, HEAPIFY_DONE,
    EXTRACT_MAX, MARK_SORTED, HEAP_SIZE_CHANGE, HEAP_SORT_COMPLETE,
    DONE
};

enum class HighlightMode { VISITED, SKIPPED, RESULT };

// One flat struct for every event (simple to store, copy, reverse and serialise).
// Only the fields listed for an event type are meaningful; the rest keep their defaults.
// This table is the event contract shared by the model (Person A) and the GUI (Person B).
//
//  Type               Fields used                                           Meaning / undo data
//  -----------------  ----------------------------------------------------  ---------------------------------------------
//  VISIT              nodeId                                                node entered; alarm +1
//  COMPARE            nodeId, key, result                                   result = sign(key - node key): -1 go left,
//                                                                           0 equal, +1 go right; alarm +1
//  INSERT             nodeId, parentId, side                                new node attached
//  UNLINK             nodeId, parentId, side                                node detached from parent's `side`
//  SWAP_VALUE         nodeId, otherId, oldValue, newValue                   oldValue = value that WAS in nodeId,
//                                                                           newValue = value that WAS in otherId
//  ROTATE             nodeId (pivot), otherId (new subtree root),           one event per primitive rotation; side = LEFT
//                     rotation, side                                        for rotateLeft, RIGHT for rotateRight;
//                                                                           rotation = case being repaired (LL/RR/LR/RL)
//                                                                           or NONE for a manual rotation. LR/RL = 2 events.
//  UPDATE_HEIGHT      nodeId, oldValue, newValue                            stored height changed
//  UPDATE_SIZE        nodeId, oldValue, newValue                            stored subtree size changed
//  BALANCE_ALERT      nodeId, balanceFactor                                 |bf| > 1 detected
//  HIGHLIGHT_SUBTREE  nodeId, mode                                          visited / skipped (pruned) / result
//  HEAP_BUILD         array (snapshot before build), heapSize, indexA       indexA = first index to sift down (n/2 - 1)
//  HEAP_SWAP          indexA, indexB, oldValue, newValue, text (reason)     oldValue = value that WAS at indexA,
//                                                                           newValue = value that WAS at indexB
//  HEAPIFY_START      indexA (start index), heapSize
//  HEAPIFY_DONE       indexA (index where sift ended), heapSize
//  EXTRACT_MAX        value (the maximum), indexA (root index = 0), heapSize (size BEFORE extraction)
//  MARK_SORTED        indexA, value                                         element now belongs to the sorted region
//  HEAP_SIZE_CHANGE   oldValue (old size), newValue (new size)
//  HEAP_SORT_COMPLETE array (final array)
//  DONE               text (summary)                                        last event of every operation's batch
struct Event {
    EventType type = EventType::DONE;
    NodeId nodeId = INVALID_ID;
    NodeId otherId = INVALID_ID;
    NodeId parentId = INVALID_ID;
    Side side = Side::NONE;
    int key = 0;
    int result = 0;
    int oldValue = 0;
    int newValue = 0;
    int value = 0;
    int balanceFactor = 0;
    RotationType rotation = RotationType::NONE;
    HighlightMode mode = HighlightMode::VISITED;
    int indexA = -1;
    int indexB = -1;
    int heapSize = 0;
    std::string text;
    std::vector<int> array;

    // Human-readable one-liner for the Event Log panel.
    std::string describe() const;
};

const char* toString(EventType type);

} // namespace vh
