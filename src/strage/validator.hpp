
#ifndef DISTRIBUTED_SYNC_VALIDATOR_HPP
#define DISTRIBUTED_SYNC_VALIDATOR_HPP

#include <endpoint.pb.h>

namespace sync {
  namespace strage {
    bool validate(const Block &block);
  }
}

#endif  // DISTRIBUTED_SYNC_VALIDATOR_HPP
