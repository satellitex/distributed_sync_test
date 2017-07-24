//
// Created by Takumi Yamashita on 2017/07/24.
//

#ifndef DISTRIBUTED_SYNC_STRAGE_HPP
#define DISTRIBUTED_SYNC_STRAGE_HPP

#include <endpoint.pb.h>
#include <exception>
#include <vector>

namespace sync {
  namespace strage {
    using Block = sync::protocol::Block;
    using Strage = std::vector<Block>;

    Strage& strage();
  }
}
#endif  // DISTRIBUTED_SYNC_STRAGE_HPP
