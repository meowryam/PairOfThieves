#pragma once
#include <string>
#include "model/Event.h"
#include "model/EventLog.h"

namespace vh {

// Operation counters, used by benchmarks (they work even when event recording is off).
struct OpStats {
    long long comparisons = 0;
    long long swaps = 0;
    long long rotations = 0;
    void reset() { *this = OpStats(); }
};

// Common base of BinaryTree, BST (and AVLTree through it) and MaxHeap.
//
// How operations return results and events (agreed contract):
//   * Every operation returns its normal result (bool / node pointer / vector ...).
//   * If an EventLog is attached and recording is on, the operation appends its events to it
//     and ends the batch with one DONE event.
//   * Usage:  EventLog log; tree.setEventLog(&log); tree.insert(5);  animator.play(log);
//   * Benchmarks: setRecording(false) (or attach no log) -> no events are created or stored.
class ModelBase {
public:
    virtual ~ModelBase() = default;

    void setEventLog(ModelEventLog* log) { log_ = log; }
    ModelEventLog* eventLog() const { return log_; }
    void setRecording(bool on) { recording_ = on; }
    bool recording() const { return recording_; }

    const OpStats& stats() const { return stats_; }
    void resetStats() { stats_.reset(); }

protected:
    // Check this before building an Event so disabled recording costs (almost) nothing.
    bool wantsEvents() const { return recording_ && log_ != nullptr; }
    void emit(const Event& e) const { if (wantsEvents()) log_->add(e); }
    void emitDone(const std::string& summary = "") const {
        if (!wantsEvents()) return;
        Event e;
        e.type = EventType::DONE;
        e.text = summary;
        log_->add(e);
    }

    ModelEventLog* log_ = nullptr;
    bool recording_ = true;
    mutable OpStats stats_;            // mutable: const queries (search, kth, ...) still count comparisons
};

} // namespace vh
