#include "model/ScoreSystem.h"
#include <algorithm>

namespace vh {

int ScoreSystem::capacityFor(int optimalSteps) {
    if (optimalSteps < 0) optimalSteps = 0;
    return (3 * optimalSteps + 1) / 2 + 2;              // ceil(1.5 * n) + 2 in integer arithmetic
}

void ScoreSystem::startLevel(int optimalSteps) {
    optimal_ = std::max(0, optimalSteps);
    capacity_ = capacityFor(optimal_);
    steps_ = penaltyAlarm_ = penaltyCount_ = penaltyPoints_ = bonus_ = 0;
    hintUsed_ = false;
}

void ScoreSystem::addStep(int n) { if (n > 0) steps_ += n; }

void ScoreSystem::applyEvents(const ModelEventLog& log) {
    for (const Event& e : log.events())
        if (e.type == EventType::VISIT || e.type == EventType::COMPARE) ++steps_;
}

void ScoreSystem::penaltyWrongTraversalClick() { penaltyAlarm_ += 1; ++penaltyCount_; }
void ScoreSystem::penaltyWrongRotation() { penaltyAlarm_ += 2; penaltyPoints_ += 50; ++penaltyCount_; }
void ScoreSystem::penaltyHintUsed() { hintUsed_ = true; ++penaltyCount_; }
void ScoreSystem::penaltyInvalidHeapOp() { penaltyAlarm_ += 1; ++penaltyCount_; }
void ScoreSystem::addBonus(int points) { bonus_ += points; }

int ScoreSystem::score() const {
    return std::max(0, 1000 - 10 * alarm() - penaltyPoints_ + bonus_);
}

int ScoreSystem::stars() const {
    if (alarmFull()) return 0;
    int s = 1;
    if (steps_ <= optimal_ && penaltyCount_ == 0) s = 3;
    else if (4 * steps_ <= 5 * optimal_ && penaltyCount_ <= 1) s = 2;   // steps <= 1.25 * optimal
    return std::min(s, starCap());
}

void Leaderboard::add(const LeaderboardEntry& entry) {
    auto it = entries_.begin();
    while (it != entries_.end() && it->score >= entry.score) ++it;
    entries_.insert(it, entry);
}

bool Leaderboard::load(const std::string&) { return false; }            // TODO
bool Leaderboard::save(const std::string&) const { return false; }      // TODO

} // namespace vh
