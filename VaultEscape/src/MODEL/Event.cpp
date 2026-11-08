#include "model/Event.h"

namespace vh {

const char* toString(EventType type) {
    switch (type) {
        case EventType::VISIT: return "VISIT";
        case EventType::COMPARE: return "COMPARE";
        case EventType::INSERT: return "INSERT";
        case EventType::UNLINK: return "UNLINK";
        case EventType::SWAP_VALUE: return "SWAP_VALUE";
        case EventType::ROTATE: return "ROTATE";
        case EventType::UPDATE_HEIGHT: return "UPDATE_HEIGHT";
        case EventType::UPDATE_SIZE: return "UPDATE_SIZE";
        case EventType::BALANCE_ALERT: return "BALANCE_ALERT";
        case EventType::HIGHLIGHT_SUBTREE: return "HIGHLIGHT_SUBTREE";
        case EventType::HEAP_BUILD: return "HEAP_BUILD";
        case EventType::HEAP_SWAP: return "HEAP_SWAP";
        case EventType::HEAPIFY_START: return "HEAPIFY_START";
        case EventType::HEAPIFY_DONE: return "HEAPIFY_DONE";
        case EventType::EXTRACT_MAX: return "EXTRACT_MAX";
        case EventType::MARK_SORTED: return "MARK_SORTED";
        case EventType::HEAP_SIZE_CHANGE: return "HEAP_SIZE_CHANGE";
        case EventType::HEAP_SORT_COMPLETE: return "HEAP_SORT_COMPLETE";
        case EventType::DONE: return "DONE";
    }
    return "?";
}

static const char* sideName(Side s) {
    return s == Side::LEFT ? "left" : (s == Side::RIGHT ? "right" : "-");
}

static const char* rotationName(RotationType r) {
    switch (r) {
        case RotationType::LL: return "LL";
        case RotationType::RR: return "RR";
        case RotationType::LR: return "LR";
        case RotationType::RL: return "RL";
        default: return "manual";
    }
}

static const char* modeName(HighlightMode m) {
    switch (m) {
        case HighlightMode::VISITED: return "visited";
        case HighlightMode::SKIPPED: return "skipped";
        case HighlightMode::RESULT: return "result";
    }
    return "?";
}

std::string Event::describe() const {
    using std::to_string;
    switch (type) {
        case EventType::VISIT:
            return "Visit room " + to_string(nodeId);
        case EventType::COMPARE: {
            const char* dir = result < 0 ? "go left" : (result > 0 ? "go right" : "match");
            return "Compare key " + to_string(key) + " with room " + to_string(nodeId) + ": " + dir;
        }
        case EventType::INSERT:
            return "Insert room " + to_string(nodeId) + " as " + sideName(side) + " child of " + to_string(parentId);
        case EventType::UNLINK:
            return "Unlink room " + to_string(nodeId) + " from " + sideName(side) + " of " + to_string(parentId);
        case EventType::SWAP_VALUE:
            return "Swap values of rooms " + to_string(nodeId) + " (" + to_string(oldValue) + ") and " +
                   to_string(otherId) + " (" + to_string(newValue) + ")";
        case EventType::ROTATE:
            return std::string("Rotate ") + sideName(side) + " at room " + to_string(nodeId) +
                   " (case " + rotationName(rotation) + "), new subtree root " + to_string(otherId);
        case EventType::UPDATE_HEIGHT:
            return "Height of room " + to_string(nodeId) + ": " + to_string(oldValue) + " -> " + to_string(newValue);
        case EventType::UPDATE_SIZE:
            return "Size of room " + to_string(nodeId) + ": " + to_string(oldValue) + " -> " + to_string(newValue);
        case EventType::BALANCE_ALERT:
            return "Imbalance at room " + to_string(nodeId) + " (balance factor " + to_string(balanceFactor) + ")";
        case EventType::HIGHLIGHT_SUBTREE:
            return "Subtree of room " + to_string(nodeId) + " marked " + modeName(mode);
        case EventType::HEAP_BUILD:
            return "Build Max Heap on " + to_string(heapSize) + " elements, start at index " + to_string(indexA);
        case EventType::HEAP_SWAP:
            return "Swap index " + to_string(indexA) + " (" + to_string(oldValue) + ") and index " +
                   to_string(indexB) + " (" + to_string(newValue) + ")" + (text.empty() ? "" : ": " + text);
        case EventType::HEAPIFY_START:
            return "Heapify from index " + to_string(indexA) + ", heap size " + to_string(heapSize);
        case EventType::HEAPIFY_DONE:
            return "Heapify finished at index " + to_string(indexA) + ", heap size " + to_string(heapSize);
        case EventType::EXTRACT_MAX:
            return "Extract maximum " + to_string(value) + " from root, heap size " + to_string(heapSize);
        case EventType::MARK_SORTED:
            return "Mark index " + to_string(indexA) + " (" + to_string(value) + ") as sorted";
        case EventType::HEAP_SIZE_CHANGE:
            return "Heap size " + to_string(oldValue) + " -> " + to_string(newValue);
        case EventType::HEAP_SORT_COMPLETE:
            return "Heap Sort complete";
        case EventType::DONE:
            return text.empty() ? "Done" : "Done: " + text;
    }
    return "?";
}

} // namespace vh
