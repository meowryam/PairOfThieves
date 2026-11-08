#pragma once
#include <string>
#include <vector>
#include "model/EventLog.h"

namespace vh {

// Alarm meter, penalties, stars and score for ONE level attempt. Pure rules, no GUI.
// Status: fully implemented (the HUD needs it from day one).
//
// Definitions (agree with Person B):
//   steps()   = VISIT + COMPARE events counted so far (plus addStep calls).
//   alarm()   = steps() + alarm added by penalties. The meter is "full" when alarm() >= alarmCapacity().
//   capacity  = ceil(1.5 * optimalSteps) + 2.
//   penalties: wrong traversal click +1 alarm | wrong rotation +2 alarm and -50 points |
//              hint used: star cap becomes 2 (applied once, however many hints) |
//              invalid heap swap / wrong parent-child comparison (Act 4) +1 alarm.
//   Every penalty call adds 1 to penaltyCount().
//   score = max(0, 1000 - 10 * alarm() - penaltyPoints() + bonus()).
//   stars (when not full): 3 if steps <= optimal and no penalties; 2 if steps <= 1.25 * optimal and
//         at most 1 penalty; otherwise 1; then limited by the hint star cap. Alarm full -> 0.
class ScoreSystem {
public:
    static int capacityFor(int optimalSteps);

    void startLevel(int optimalSteps);                  // reset everything for a new attempt

    void addStep(int n = 1);                            // extra alarm steps outside events
    void applyEvents(const ModelEventLog& log);              // +1 step per VISIT and per COMPARE event
    void penaltyWrongTraversalClick();
    void penaltyWrongRotation();
    void penaltyHintUsed();
    void penaltyInvalidHeapOp();
    void addBonus(int points);

    int optimalSteps() const { return optimal_; }
    int alarmCapacity() const { return capacity_; }
    int steps() const { return steps_; }
    int alarm() const { return steps_ + penaltyAlarm_; }
    bool alarmFull() const { return alarm() >= capacity_; }
    int penaltyCount() const { return penaltyCount_; }
    int penaltyPoints() const { return penaltyPoints_; }
    int bonus() const { return bonus_; }
    int starCap() const { return hintUsed_ ? 2 : 3; }
    int score() const;
    int stars() const;

private:
    int optimal_ = 0;
    int capacity_ = 2;
    int steps_ = 0;
    int penaltyAlarm_ = 0;
    int penaltyCount_ = 0;
    int penaltyPoints_ = 0;
    int bonus_ = 0;
    bool hintUsed_ = false;
};

// Local leaderboard (Endless mode). Entries are kept sorted by score, highest first.
struct LeaderboardEntry {
    std::string name;
    int score = 0;
    std::string mode;                                   // e.g. "endless"
};

class Leaderboard {
public:
    void add(const LeaderboardEntry& entry);            // implemented: sorted insert
    const std::vector<LeaderboardEntry>& entries() const { return entries_; }
    bool load(const std::string& path);                 // TODO: read the local file; false on failure
    bool save(const std::string& path) const;           // TODO: write the local file; false on failure
private:
    std::vector<LeaderboardEntry> entries_;
};

} // namespace vh
