#ifndef DISTRIBUTED_SYNC_PEERSSERVER_HPP
#define DISTRIBUTED_SYNC_PEERSSERVER_HPP

#include <endpoint.pb.h>
#include <endpoint.grpc.pb.h>

namespace peers {
  namespace server {

    using Peer = sync::protocol::Peer;
    using AddPeer = sync::protocol::AddPeer;
    using CommitResponse = sync::protocol::CommitResponse;

    void run();

    class PeersServer : public Peer::Service {
     public:

      ::grpc::Status addPeer(::grpc::ServerContext* context, const AddPeer* addPeer,
                        CommitResponse* commitResponse) override;

    };
  };
}

#endif  // DISTRIBUTED_SYNC_PEERSSERVER_HPP
