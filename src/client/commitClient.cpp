#include <client/commitClient.hpp>
#include <strage/strage.hpp>

#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_map>

#include <grpc/support/log.h>

namespace commit {
  namespace client {

    using CommitResponse = sync::protocol::CommitResponse;

    void commit(const Block &block) {
      static std::unordered_map<std::string, std::unique_ptr<CommitClient>>
          clients;
      for (auto &p : sync::strage::peers()) {
        if (!clients.count(p)) clients[p] = std::make_unique<CommitClient>(p);
        clients[p]->send(block);
      }
    }

    CommitClient::CommitClient(std::string ip) {
      stub_ = Commit::NewStub(::grpc::CreateChannel(
          ip + ":50052", grpc::InsecureChannelCredentials()));
    }

    void CommitClient::send(const Block &block) {
      CommitResponse response;

      ::grpc::ClientContext context;
      ::grpc::CompletionQueue cq;
      ::grpc::Status status;

      std::cout << "sennd Async!!" << std::endl;
      auto rpc = std::move(stub_->AsynccommitBlock(&context, block, &cq));
      std::cout << "pre thread!!" << std::endl;

      std::cout << "in thread!!" << std::endl;
      rpc->Finish(&response, &status, (void *)1);

      void *got_tag;
      bool ok = false;
      if (!cq.AsyncNext(&got_tag, &ok, (gpr_timespec){(int64_t)1, (int32_t)500,
                                                      GPR_TIMESPAN})) {
        throw std::runtime_error("CompletionQueue::Next() returns error");
      }

      if (got_tag != (void *) 1)
        std::cout << "TimeOut" << std::endl;
      else {
        GPR_ASSERT(got_tag == (void *)1);
        if (status.ok()) {
          std::cout << "SucessStatus: " << response.status() << std::endl;
        } else {
          std::cout << "RPC failed" << std::endl;
        }
      }
    }
  }
}