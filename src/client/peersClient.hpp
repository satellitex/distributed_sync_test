#ifndef DISTRIBUTED_SYNC_PEERSCLIENT_HPP
#define DISTRIBUTED_SYNC_PEERSCLIENT_HPP

#include <endpoint.pb.h>
#include <endpoint.grpc.pb.h>

namespace peers {
  namespace service {

    using Peer = sync::protocol::Peer;

    class PeersClient {
      PeersClient(std::string ip);
      bool addPeer();
    };
    std::unique_ptr<Peer::Stub> stub_;
  }
}

#endif  // DISTRIBUTED_SYNC_PEERSCLIENT_HPP
