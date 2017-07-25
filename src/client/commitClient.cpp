#include <client/commitClient.hpp>
#include <helper/ip_tools.hpp>

#include <iostream>
#include <thread>

#include <grpc/support/log.h>

namespace commit {
  namespace client {

    using CommitResponse = sync::protocol::CommitResponse;

    void CommitClient::commit(const Block &block) {
      this->send(helper::getMyIp(), block);
    }

    void CommitClient::send(std::string ip, const Block &block) {
      static auto stub_ = Commit::NewStub(::grpc::CreateChannel(
          ip + ":50051", grpc::InsecureChannelCredentials()));

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
