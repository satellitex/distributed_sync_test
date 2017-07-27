#include <server/peersServer.hpp>
#include <strage/strage.hpp>
#include <helper/ip_tools.hpp>

#include <grpc++/grpc++.h>

namespace peers {
  namespace server {

    using Peer = sync::protocol::Peer;
    using AddPeer = sync::protocol::AddPeer;
    using CommitResponse = sync::protocol::CommitResponse;

    void run() {
      std::string server_address(helper::getMyIp() + ":50053");
      peers::server::PeersServer service;

      ::grpc::ServerBuilder builder;
      builder.AddListeningPort(server_address,
                               ::grpc::InsecureServerCredentials());
      builder.RegisterService(&service);
      std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
      std::cout << "Server listening on " << server_address << std::endl;
      server->Wait();
    }

    ::grpc::Status PeersServer::addPeer(::grpc::ServerContext* context,
                                        const AddPeer* addPeer,
                                        CommitResponse* commitResponse) {
      auto ip = addPeer->peer();
      sync::strage::addPeer(ip);

      commitResponse->set_status(CommitResponse::SUCCESS);
      return ::grpc::Status::OK;
    }
  }
}