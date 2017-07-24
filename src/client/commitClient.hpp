#ifndef DISTRIBUTED_SYNC_COMMITCLIENT_HPP
#define DISTRIBUTED_SYNC_COMMITCLIENT_HPP

#include <endpoint.pb.h>
#include <endpoint.grpc.pb.h>

#include <grpc++/grpc++.h>

namespace commit {
  namespace client {

    using Block = sync::protocol::Block;
    using Commit = sync::protocol::Commit;

    class CommitClient {
    public:
      void commit(const Block &block);
      void send(std::string ip, const Block &block);

     private:
      std::unique_ptr<Commit::Stub> stub_;
    };
  }
}

#endif  // DISTRIBUTED_SYNC_COMMITCLIENT_HPP
