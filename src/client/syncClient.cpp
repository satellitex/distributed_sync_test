#include <chrono>
#include <thread>
#include <unordered_map>

#include <client/syncClient.hpp>
#include <strage/strage.hpp>
#include <strage/validator.hpp>

#include <grpc++/grpc++.h>

namespace sync {
  namespace client {
    using Request = sync::protocol::Request;

    void blockDownload(const Block& block) {
      static std::unordered_map<std::string, std::unique_ptr<SyncClient>> clients_;
      auto target_ip = block.creator();
      if (!clients_.count(target_ip))
        clients_[target_ip] = std::make_unique<SyncClient>(target_ip);
      // size()番目からBlockが無いので欲しい
      clients_[target_ip]->fetchBlocks(sync::strage::strage().size());
    }

    SyncClient::SyncClient(std::string ip) {
      stub_ = Sync::NewStub(::grpc::CreateChannel(
          ip + ":50051", ::grpc::InsecureChannelCredentials()));
    }

    void SyncClient::fetchBlocks(uint64_t offset) {
      std::cout << "fetchBlocks!!" << std::endl;
      ::grpc::ClientContext context;

      std::shared_ptr<::grpc::ClientReaderWriter<Request, Block>> stream(
          stub_->fetchBlocks(&context));

      Request request;
      request.set_offset(offset);

      stream->Write(request);

      std::thread writer([&stream]() {
        while (sync::strage::status().unsynced())
          ;
        std::cout << "synced!!" << std::endl;
        Request request;
        request.set_offset(-1);
        stream->Write(request);

        stream->WritesDone();
      });

      Block res_block;
      while (stream->Read(&res_block)) {
        std::cout << "Read Block!!" << std::endl;
        std::cout << "id: " << res_block.id() << std::endl;
        std::cout << "context: " << res_block.context() << std::endl;

        if (sync::strage::validate(res_block)) {
          sync::strage::strage().emplace_back(res_block);
        }

        std::cout << "status: " << sync::strage::status().synced() << std::endl;
      }

      writer.join();
      ::grpc::Status status = stream->Finish();
      if (!status.ok()) {
        std::cout << "fetchBlock rpc Failed." << std::endl;
      } else {
        std::cout << "fetchBlock rpc Success!" << std::endl;
      }
    }
  }
}