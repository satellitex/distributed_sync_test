#include <client/peersClient.hpp>
#include <helper/ip_tools.hpp>

#include <chrono>
#include <thread>

#include <grpc++/grpc++.h>

namespace peers {
  namespace client {

    using AddPeer = sync::protocol::AddPeer;
    using CommitResponse = sync::protocol::CommitResponse;

    PeersClient::PeersClient(std::string ip) {
      stub_ = Peer::NewStub(::grpc::CreateChannel(
          ip + ":50053", grpc::InsecureChannelCredentials()));

      // wait 1 sec
      std::chrono::milliseconds wait(1000);
      std::this_thread::sleep_for(wait);
    }

    bool PeersClient::addPeer() {
      ::grpc::ClientContext context;

      AddPeer request;
      request.set_peer(helper::getMyIp());
      CommitResponse response;

      ::grpc::Status status = stub_->addPeer(&context, request, &response);

      if (!status.ok()) {
        std::cout << "AddPeer rpc failed." << std::endl;
        return false;
      }
      std::cout << "AddPeer rpc succeed!" << std::endl;
      return true;
    }
  }
}
