#ifndef DISTRIBUTEDSYNCTEST_SYNCSERVER_HPP
#define DISTRIBUTEDSYNCTEST_SYNCSERVER_HPP

#include <string>

namespace sync {
  namespace server {
    class SyncServer {
      void responseBlocks(std::string return_ip, uint64_t offset);
    };
  }
}

#endif //DISTRIBUTEDSYNCTEST_SYNCSERVER_HPP
