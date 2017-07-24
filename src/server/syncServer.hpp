#ifndef DISTRIBUTEDSYNCTEST_SYNCSERVER_HPP
#define DISTRIBUTEDSYNCTEST_SYNCSERVER_HPP

#include <endpoint.grpc.pb.h>
#include <string>

#include <grpc++/grpc++.h>

namespace sync {
  namespace server {

    using Sync = sync::protocol::Sync;
    using Request = sync::protocol::Request;
    using Block = sync::protocol::Block;

    void run();
    class SyncServer : public Sync::Service {
      ::grpc::Status fetchBlocks(::grpc::ServerContext* context,
                                 const Request* rectangle,
                                 ::grpc::ServerWriter<Block>* writer) override;
    };
  }
}

#endif  // DISTRIBUTEDSYNCTEST_SYNCSERVER_HPP
