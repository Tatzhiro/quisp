#include "EnoughResourceClause.h"

namespace quisp::rules::active::clauses {

bool EnoughResourceClause::check(std::multimap<int, IStationaryQubit *> &resource) {
  bool enough = false;
  int num_free = 0;

  for (auto it = resource.begin(); it != resource.end(); ++it) {
    if (it->first == partner) {
      if (!it->second->isLocked()) {  // here must have loop
        num_free++;
      }
      if (num_free >= num_resource_required) {
        enough = true;
      }
    }
  }
  return enough;
}
}  // namespace quisp::rules::active::clauses
