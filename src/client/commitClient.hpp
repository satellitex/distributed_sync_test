#ifndef DISTRIBUTED_SYNC_COMMITCLIENT_HPP
#define DISTRIBUTED_SYNC_COMMITCLIENT_HPP

#include <endpoint.grpc.pb.h>
#include <endpoint.pb.h>

#include <grpc++/grpc++.h>

namespace commit {
  namespace client {

    using Block = sync::protocol::Block;
    using Commit = sync::protocol::Commit;

    void commit(const Block &block);

    class CommitClient {
     public:
      CommitClient(std::string ip);
      void send(const Block &block);

     private:
      std::unique_ptr<Commit::Stub> stub_;
    };
  }
}

#endif  // DISTRIBUTED_SYNC_COMMITCLIENT_HPP
