#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include "model/Event.h"

namespace vh {

// Ordered list of events produced by one operation (or several, if the caller does not clear it).
// The model only appends; the GUI's AnimationController only reads.
class ModelEventLog {
public:
    void add(const Event& e) { events_.push_back(e); }       // append
    void clear() { events_.clear(); }
    std::size_t size() const { return events_.size(); }
    bool empty() const { return events_.empty(); }
    const Event& at(std::size_t i) const { return events_.at(i); }   // throws std::out_of_range
    const std::vector<Event>& events() const { return events_; }

    std::vector<Event> reversed() const;                     // copy in reverse order (for inverse playback)
    std::vector<std::string> describeAll() const;            // one line per event for the Event Log panel

private:
    std::vector<Event> events_;
};

} // namespace vh
