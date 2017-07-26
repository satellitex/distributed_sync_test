#include <client/commitClient.hpp>
#include <strage/strage.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>

#include <grpc/support/log.h>

namespace commit {
  namespace client {

    using CommitResponse = sync::protocol::CommitResponse;

    void commit(const Block &block) {
      static std::unordered_map<std::string,std::unique_ptr<CommitClient>> clients;

      for( auto &p : sync::strage::peers() ){
        if( !clients.count(p) )
          clients[p] = std::make_unique<CommitClient>( p );
        clients[p]->send(block);
      }

    }

    CommitClient::CommitClient(std::string ip) {
      stub_ = Commit::NewStub(::grpc::CreateChannel(
          ip + ":50051", grpc::InsecureChannelCredentials()));

      // wait 1 sec
      std::chrono::milliseconds wait(1000);
      std::this_thread::sleep_for(wait);
    }

    void CommitClient::send(const Block &block) {
      CommitResponse response;

      ::grpc::ClientContext context;
      ::grpc::CompletionQueue cq;
      ::grpc::Status status;

      std::cout << "sennd Async!!" << std::endl;
      auto rpc = std::move(stub_->AsynccommitBlock(&context, block, &cq));
      std::cout << "pre thread!!" << std::endl;

      std::thread th([&]() {
        std::cout << "in thread!!" << std::endl;
        rpc->Finish(&response, &status, (void *)1);

        void *got_tag;
        bool ok = false;

        GPR_ASSERT(cq.Next(&got_tag, &ok));
        GPR_ASSERT(got_tag == (void *)1);
        GPR_ASSERT(ok);

        if (status.ok()) {
          std::cout << "SucessStatus: " << response.status() << std::endl;
        } else {
          std::cout << "RPC failed" << std::endl;
        }
      });
      th.join();
    }
  }
}
