#include "model/EventLog.h"
#include <algorithm>

namespace vh {

std::vector<Event> ModelEventLog::reversed() const {
    std::vector<Event> out(events_);
    std::reverse(out.begin(), out.end());
    return out;
}

std::vector<std::string> ModelEventLog::describeAll() const {
    std::vector<std::string> out;
    out.reserve(events_.size());
    for (const Event& e : events_) out.push_back(e.describe());
    return out;
}

} // namespace vh
