#include "ActiveRuleSet.h"

namespace quisp::rules::active {
/**
 * @brief Construct a new ActiveRuleSet.
 *
 * @param _ruleset_id
 * @param _owner_addr
 */
ActiveRuleSet::ActiveRuleSet(unsigned long _ruleset_id, int _owner_addr) : ruleset_id(_ruleset_id), owner_addr(_owner_addr) {}

void ActiveRuleSet::addRule(std::unique_ptr<ActiveRule> r) { rules.emplace_back(std::move(r)); };
std::unique_ptr<ActiveRule>& ActiveRuleSet::getRule(int i) { return rules[i]; };
int ActiveRuleSet::size() const { return rules.size(); };
bool ActiveRuleSet::empty() const { return rules.empty(); }
std::vector<std::unique_ptr<ActiveRule>>::const_iterator ActiveRuleSet::cbegin() { return rules.cbegin(); }
std::vector<std::unique_ptr<ActiveRule>>::const_iterator ActiveRuleSet::cend() { return rules.cend(); }

}  // namespace quisp::rules::active
