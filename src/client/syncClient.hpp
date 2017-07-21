//
// Created by Takumi Yamashita on 2017/07/21.
//

#ifndef DISTRIBUTEDSYNCTEST_SYNCCLIENT_HPP
#define DISTRIBUTEDSYNCTEST_SYNCCLIENT_HPP

#include <string>

namespace sync {
  namespace client {
    class SyncClient {
      void fetchBlock(std::string ip,uint64_t offset);
    };
  }
}

#endif //DISTRIBUTEDSYNCTEST_SYNCCLIENT_HPP
