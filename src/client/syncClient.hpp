#ifndef DISTRIBUTEDSYNCTEST_SYNCCLIENT_HPP
#define DISTRIBUTEDSYNCTEST_SYNCCLIENT_HPP

#include <endpoint.grpc.pb.h>
#include <grpc++/channel.h>
#include <string>

namespace sync {
  namespace client {

    using Sync = sync::protocol::Sync;

    class SyncClient {
     public:
      SyncClient(std::string ip);

      void fetchBlocks(uint64_t offset);
     private:
      std::unique_ptr<Sync::Stub> stub_;
    };
  }
}

#endif  // DISTRIBUTEDSYNCTEST_SYNCCLIENT_HPP
