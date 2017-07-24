#include <client/syncClient.hpp>
#include <strage/strage.hpp>

#include <grpc++/grpc++.h>

namespace sync {
  namespace client {
    using Request = sync::protocol::Request;
    using Block = sync::protocol::Block;
    void SyncClient::fetchBlocks(std::string ip, uint64_t offset) {
      stub_ = Sync::NewStub(::grpc::CreateChannel(
          ip + ":50051", ::grpc::InsecureChannelCredentials()));

      Request request;
      request.set_offset(offset);

      ::grpc::ClientContext context;

      std::cout << "send fetchBlocks :" << std::endl;
      std::cout << "offset: " << offset << std::endl;

      std::unique_ptr<::grpc::ClientReader<Block>> reader(
          stub_->fetchBlocks(&context, request));

      Block block;
      while (reader->Read(&block)) {
        std::cout << "Read Block!!" << std::endl;
        std::cout << "id: " << block.id() << std::endl;
        std::cout << "context: " << block.context() << std::endl;
        sync::strage::strage().emplace_back(block);
      }

      ::grpc::Status status = reader->Finish();
      if (status.ok())
        std::cout << "fetchBlocks rpc succeded." << std::endl;
      else
        std::cout << "fetchBlocks rpc fialed." << std::endl;
    }
  }
}